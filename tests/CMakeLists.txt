cmake_minimum_required(VERSION 3.10)

include(${CMAKE_SOURCE_DIR}/cmake/FindQt.cmake)
include_directories(${CONAN_INCLUDE_DIRS_GTEST})
include_directories(${CMAKE_SOURCE_DIR}/view_and_compress)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/view_and_compress/*/*.cpp)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/view_and_compress/*/*.h)

add_subdirectory(TestProcessModel)
add_subdirectory(ProcessActionMocks)
