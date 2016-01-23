cmake_minimum_required(VERSION 2.6)
project(pendulum)

find_package(GLUT)
find_package(OpenGL)
add_definitions("-std=c++0x")

include_directories(${CMAKE_SOURCE_DIR})

include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})

add_executable(gl_pendulum gl_pendulum.cpp)
target_link_libraries(gl_pendulum ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra  -std=c++0x")
endif()
