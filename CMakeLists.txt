cmake_minimum_required(VERSION 2.6)
project(pendulum)

find_package(GLUT)
find_package(OpenGL)
add_definitions("-std=c++0x")

include_directories(${CMAKE_SOURCE_DIR})

include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})

add_executable(gl_pendulum gl_pendulum.cpp)
target_link_libraries(gl_pendulum ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
