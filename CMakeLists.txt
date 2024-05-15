cmake_minimum_required(VERSION 3.24.2)
project(Computer_graphics_GLUT_lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)
target_link_libraries(main -lglew32 -lopengl32 -lfreeglut)
