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

target_link_libraries(${PROJ_NAME}
    PRIVATE
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
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

juce_generate_juce_header(${PROJ_NAME})

add_subdirectory(src)