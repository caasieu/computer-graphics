cmake_minimum_required(VERSION 3.6)
project(recap)

add_executable(recap main.cpp glad.c)

target_include_directories(recap PRIVATE include)


# Encontra e inclui o OpenGL
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_library(SOIL2 soil2)

target_link_libraries(recap PRIVATE OpenGL::GL)
target_link_libraries(recap PRIVATE glfw)
target_link_libraries(recap PRIVATE soil2)
