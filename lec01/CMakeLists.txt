project(lec01)

add_executable(lec01_basic basic.cpp)

add_executable(lec01_average average.cpp)
target_link_libraries (lec01_average gtest_main)

