cmake_minimum_required(VERSION 3.6)
project(multiple)

add_executable(multiple main.cpp glad.c Utils.cpp)

target_include_directories(multiple PRIVATE include)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(SOIL2 soil2)

target_link_libraries(multiple PRIVATE OpenGL::GL)
target_link_libraries(multiple PRIVATE glfw)
#target_link_libraries(multiple PRIVATE soil2)