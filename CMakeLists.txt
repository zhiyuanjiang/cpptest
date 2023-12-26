cmake_minimum_required(VERSION 3.22)
project(cpptest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pipe -fPIC -g")

add_executable(test test.cpp)

add_subdirectory(test_timer)