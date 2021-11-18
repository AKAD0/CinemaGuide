cmake_minimum_required(VERSION 3.16)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")

set(LIB_SOURCE_FILES_STATIC user_account.cpp)
add_library(user_account STATIC ${LIB_SOURCE_FILES_STATIC})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})    
add_executable(user_test user_test.cpp)
target_link_libraries(user_test ${GTEST_LIBRARIES} user_account)