set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pipe -fPIC -g")

add_executable(test_align test_align.cpp)
add_executable(test_aligned_storage test_aligned_storage.cpp)