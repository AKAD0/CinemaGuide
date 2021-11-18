cmake_minimum_required(VERSION 3.9.2)
project(movie)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(TEST test_movie.cpp)

target_include_directories(TEST PUBLIC ${INC_DIR})

target_link_libraries(TEST ${GTEST_LIBRARIES})

enable_testing()

#add_executable()
