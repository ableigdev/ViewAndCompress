cmake_minimum_required(VERSION 3.10)

project(view_and_compress)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 14)
add_definitions(-fPIC)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Set variables
include(${CMAKE_SOURCE_DIR}/cmake/SetEnv.cmake)

add_subdirectory(${PROJECT_FOLDER})
add_subdirectory(tests)

# Install targets
include(${CMAKE_SOURCE_DIR}/cmake/InstallConfig.cmake)
