cmake_minimum_required(VERSION 3.22)
project(cpptest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pipe -fPIC -g")

add_executable(test test.cpp)
add_executable(test_function_type test_function_type.cpp)

add_subdirectory(test_clock)
add_subdirectory(test_memory)
add_subdirectory(test_align)
add_subdirectory(test_thread)