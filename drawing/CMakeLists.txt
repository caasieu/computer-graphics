cmake_minimum_required(VERSION 3.6)
project(drawing)

add_executable(drawing main.cpp glad.c Utils.cpp)

target_include_directories(drawing PRIVATE include)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(SOIL2 soil2)

target_link_libraries(drawing PRIVATE OpenGL::GL)
target_link_libraries(drawing PRIVATE glfw)
#target_link_libraries(drawing PRIVATE soil2)