cmake_minimum_required(VERSION 3.22)

# Define project name
project(ece309_spr25_hw2)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Enforce this standard

# Add Google Test directory
include_directories(Google_test/lib/include)
link_directories(Google_test/lib)

# Add the subdirectory for Google Test if you have it
add_subdirectory(Google_test)

# Define executable target and link with Google Test
add_executable(test_interval test_interval.cpp Interval.cpp)
target_link_libraries(test_interval gtest_main)
