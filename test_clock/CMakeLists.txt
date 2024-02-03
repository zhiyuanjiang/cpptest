set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pipe -fPIC -g")

add_executable(test_timer test_timer.cpp)
add_executable(test_chrono_clock test_chrono_clock.cpp)
add_executable(test_chrono_clock_format test_chrono_clock_format.cpp)
add_executable(test_ctime_clock test_ctime_clock.cpp)
add_executable(test_ctime_clock_format test_ctime_clock_format.cpp)
add_executable(test_gettimeofday test_gettimeofday.cpp)

target_link_libraries(test_chrono_clock -lpthread)
target_link_libraries(test_chrono_clock_format -lpthread)
target_link_libraries(test_ctime_clock -lpthread)
