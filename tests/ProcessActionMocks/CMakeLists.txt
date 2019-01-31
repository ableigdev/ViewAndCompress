cmake_minimum_required(VERSION 3.10)

project(ProcessActionMocks)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ProcessActionMocks.cpp) 

# Target Draco library
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
