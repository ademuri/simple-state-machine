cmake_minimum_required(VERSION 3.11)
project(simple-state-machine CXX)
set(CMAKE_CXX_STANDARD 11)

# Generate the file needed for YCM integration
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_library(simple-state-machine
  src/state-manager.h)
set_target_properties(simple-state-machine PROPERTIES LINKER_LANGUAGE CXX)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(simple-state-machine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:src>)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # TODO: add tests
endif()


