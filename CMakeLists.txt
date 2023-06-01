cmake_minimum_required(VERSION 3.9)
project(For_OpenGL_Lab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(For_OpenGL_Lab main.cpp)

target_link_libraries(For_OpenGL_Lab opengl32 glu32 freeglut)