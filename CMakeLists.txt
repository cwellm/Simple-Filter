# Simple Filter
#  
#  Copyright (C) 2023 Christoph Wellm <christoph.wellm@creaflect.de>
#
#  This program is free software: you can redistribute it and/or modify it under the terms of the 
#  GNU General Public License version 3 as published by the Free Software Foundation.
#  
#  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
#  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
#  General Public License for more details. 
#  
#  You should have received a copy of the GNU General Public License along with this program.  
#  If not, see <http://www.gnu.org/licenses/>.
#   
#  SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.20)

set(PROJ_NAME "Simple_Filter")
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

project(${PROJ_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

# makes JUCE CMake API available
message(STATUS "Trying to find JUCE...")
add_subdirectory(JUCE)
message(STATUS "JUCE found!")

if (CMAKE_BUILD_TYPE)
	message(STATUS "Build type = ${CMAKE_BUILD_TYPE}")
endif()

if (CLANG_COMPILER)
    unset(CLANG_COMPILER CACHE)
    message(STATUS "Project is being built with CLang toolchain.")
    set(CMAKE_CXX_COMPILER foo)
    #set(CMAKE_C_COMPILER)
endif()

#//  global compilation flag configuring windows sdk headers
#//  preventing inclusion of min and max macros clashing with <limits>
#define NOMINMAX 1

#//  override byte to prevent clashes with <cstddef>
#define byte win_byte_override

#add_compile_definitions(NOMINMAX=1 byte=win_byte_override)
#add_compile_definitions(_HAS_STD_BYTE=0)

juce_add_plugin(${PROJ_NAME}
	VERSION ${PROJECT_VERSION}
	FORMATS VST3 Standalone
	IS_SYNTH FALSE
	NEEDS_MIDI_INPUT TRUE
	#COPY_PLUGIN_AFTER_BUILD TRUE
	#VST3_COPY_DIR ${CUSTOM_INSTALL_PATH}
)

target_compile_definitions(${PROJ_NAME}
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

add_subdirectory(src)

# set and link libraries
set(public_libs 
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags   
)

set(private_libs 
    # AudioPluginData           # If we'd created a binary data target, we'd link to it here
    juce::juce_audio_utils#
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
)

# linking and JuceHeader for project target
target_link_libraries(${PROJ_NAME}
    PRIVATE
        ${private_libs}
    PUBLIC
        ${public_libs}
)
juce_generate_juce_header(${PROJ_NAME})

# --------------------------------------------------------------
# ---------------------- Add Test project ----------------------
# include tests
option(WITH_TESTS "Determines whether tests are included in the build.")
if (WITH_TESTS)

    add_executable(Test${PROJ_NAME})

    get_target_property(plugin_include_dirs ${PROJ_NAME} INCLUDE_DIRECTORIES)
    get_target_property(plugin_linking_dirs ${PROJ_NAME} LINK_DIRECTORIES)
    get_target_property(plugin_linking_libs ${PROJ_NAME} LINK_LIBRARIES)

    #string(REPLACE juce_audio_plugin_client "" mod_plugin_include_dirs ${plugin_include_dirs})
    #string(REPLACE juce_audio_plugin_client "" mod_plugin_linking_dirs ${plugin_linking_dirs})
    string(REPLACE juce_audio_plugin_client_utils.cpp  mod_plugin_linking_libs ${plugin_linking_libs})

    target_include_directories(Test${PROJ_NAME} PUBLIC ${plugin_include_dirs})
    target_link_directories(Test${PROJ_NAME} PUBLIC ${plugin_linking_dirs})
    target_link_libraries(Test${PROJ_NAME} PUBLIC ${mod_plugin_linking_libs})

    add_subdirectory(test)

    add_library(custom_sources STATIC
    src/Filter.cpp 
    src/IRFilter.cpp
    src/TFFilter.cpp
    src/RingBuffer.cpp
    src/Chainable.cpp
    src/FilterChain.cpp
    src/BiquadFilter.cpp
    src/BiquadCoeff.cpp
    src/BandpassFilter.cpp
    )
    target_compile_options(custom_sources PUBLIC /std:c++17)

    target_link_libraries(Test${PROJ_NAME}
        PRIVATE
            ${private_libs}
            custom_sources
        PUBLIC
            ${public_libs}
    )

    # juce_generate_juce_header(Test${PROJ_NAME}) # needs to be on this level
    target_include_directories(Test${PROJ_NAME} PUBLIC src)

    include(GoogleTest)
    enable_testing()
    gtest_discover_tests(Test${PROJ_NAME}) # from CMake itself
endif()

# --------------------------------------------------------------
# ---------------------- Copy Artifact -------------------------
add_custom_command(TARGET ${PROJ_NAME}_VST3
POST_BUILD
COMMAND cmake -E copy "$<TARGET_FILE:${PROJ_NAME}_VST3>" "${ROOT_DIR}/artifacts/$<TARGET_FILE_NAME:${PROJ_NAME}_VST3>"
)

message(STATUS "Generation of build tree successful.")

# --------------------------------------------------------------
# ---------------------- Tidying up ----------------------------

message(STATUS "Tidying up...")
