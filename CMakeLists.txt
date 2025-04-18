cmake_minimum_required(VERSION 3.22)
project(cpptest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pipe -fPIC -g")

add_executable(test test.cpp)
add_executable(test_function_type test_function_type.cpp)
add_executable(my_shared_ptr my_shared_ptr.cpp)
add_executable(my_unique_ptr my_unique_ptr.cpp)
add_executable(copy_constructors copy_constructors.cpp)
add_executable(my_memory_pool my_memory_pool.cpp)
add_executable(my_thread_pool my_thread_pool.cpp)

add_subdirectory(test_clock)
add_subdirectory(test_memory)
add_subdirectory(test_align)
add_subdirectory(test_thread)
add_subdirectory(test_algorithm)