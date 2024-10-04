cmake_minimum_required(VERSION 3.6)
project(hierarchy)

add_executable(hierarchy main.cpp glad.c Utils.cpp include/classes/Object.cpp)

target_include_directories(hierarchy PRIVATE include)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(SOIL2 soil2)

target_link_libraries(hierarchy PRIVATE OpenGL::GL)
target_link_libraries(hierarchy PRIVATE glfw)
#target_link_libraries(hierarchy PRIVATE soil2)
