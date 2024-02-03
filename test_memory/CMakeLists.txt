set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pipe -fPIC -g")

add_executable(test_circular_ref test_circular_ref.cpp)