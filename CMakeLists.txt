cmake_minimum_required(VERSION 3.16)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")



#add_executable(main main.cpp)


set(LIB_SOURCE_FILES_STATIC database.cpp)
add_library(database STATIC ${LIB_SOURCE_FILES_STATIC})
#target_link_libraries(main database)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})    
add_executable(database_test database_test.cpp)
target_link_libraries(database_test ${GTEST_LIBRARIES} database)
