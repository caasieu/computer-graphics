cmake_minimum_required(VERSION 3.6)
project(one)

add_executable(one main.cpp glad.c)

target_include_directories(one PRIVATE include)


# Encontra e inclui o OpenGL
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_library(SOIL2 soil2)

target_link_libraries(one PRIVATE OpenGL::GL)
target_link_libraries(one PRIVATE glfw)
target_link_libraries(one PRIVATE soil2)