cmake_minimum_required(VERSION 4.0.0)
project(tetris VERSION 1.0.0)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(tetris
               src/config.h
               src/main.cpp 
               src/libraries/glad.c
               src/classes/shader.h
)

target_include_directories(tetris PRIVATE dependencies)

target_link_libraries(tetris glfw)