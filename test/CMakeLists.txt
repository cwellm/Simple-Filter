message(STATUS "Including tests...")

cmake_minimum_required(VERSION 3.20)
project(Test${PROJ_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# -------------------------------------
# --- Add test files and gtest libs ---

target_sources(Test${PROJ_NAME} PRIVATE
    TestEditor.cpp
    TestProcessor.cpp
    TestRingBuffer.cpp
    TestFilter.cpp
    TestTFFilter.cpp
    TestBiquadFilter.cpp
    TestBiquadCoeff.cpp
    TestFilterChain.cpp
)

target_link_libraries(
    Test${PROJ_NAME}
    PRIVATE
        GTest::gtest_main
        GTest::gmock_main
)
