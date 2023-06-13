cmake_minimum_required(VERSION 3.9)
project(OpenGL_Lab5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(OpenGL_Lab5 main.cpp)

target_link_libraries(OpenGL_Lab5 opengl32 glu32 freeglut)