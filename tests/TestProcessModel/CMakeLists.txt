 cmake_minimum_required(VERSION 3.10)

 project(TestProcessModel)
 add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} TestProcessModel.cpp)

 # Use the Widgets module from Qt 5
 target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
 target_link_libraries(${PROJECT_NAME} Qt5::Core)
 target_link_libraries(${PROJECT_NAME} Qt5::3DCore)
 target_link_libraries(${PROJECT_NAME} Qt5::3DExtras)
 # Target Draco library
 target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
