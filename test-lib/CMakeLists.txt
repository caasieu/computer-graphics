cmake_minimum_required(VERSION 3.6)
project(test-lib)
add_executable(test-lib main.cpp lib/Car.cpp)

target_include_directories(test-lib PRIVATE lib)