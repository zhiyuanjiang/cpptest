set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pipe -fPIC -g")

add_executable(test_timer test_timer.cpp)
add_executable(test_cpp_clock test_cpp_clock.cpp)

target_link_libraries(test_cpp_clock -lpthread)