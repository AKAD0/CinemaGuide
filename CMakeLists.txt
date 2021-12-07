cmake_minimum_required(VERSION 3.16)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")

#mysql.h
#g++ -Wall -I/usr/include/mysql-cppconn-8 -o testapp main.cpp -L/usr/lib -lmysqlcppconn

#set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR usr/include/mysql-cppconn-8) find package mysql.h
# if not - crush



add_executable(main main.cpp)


set(LIB_SOURCE_FILES_STATIC database.cpp)
add_library(database STATIC ${LIB_SOURCE_FILES_STATIC})
target_link_libraries(main database)


#list(CMAKE_MODULE_PATH APPEND)
#find_package(MySQL REQUIRED)

#include_directories(${MYSQL_INCLUDE_DIR})
#target_link_libraries(cgm ${MYSQL_LIB})

#target_link_libraries(main mysqlclient)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")    
#find_package(MySQL)
#pkg_check_modules(MySQL REQUIRED mysqlclient>=5.7)

#target_link_libraries(database ${MYSQL_LIBRARY})

#target_link_libraries(database mysqlclient)

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
#find_package(MySQL REQUIRED >=8.0) # FOO_INCLUDE_DIR, FOO_LIBRARIES
#find_package(Boo REQUIRED) # BOO_INCLUDE_DIR, BOO_LIBRARIES


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")   
message("before") 
find_package(MySQL)
message("after")

include_directories("${MYSQL_INCLUDE_DIR}")

#include_directories("${BOO_INCLUDE_DIR}")
#add_executable(mysql mysql.hpp)
target_link_libraries(database ${MYSQL_LIBRARIES})





set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "/usr/include/mysql-cppconn-8/jdbc")
#include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories("${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}")
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

target_link_libraries(main mysqlcppconn)
target_compile_features(main PRIVATE cxx_range_for)  



enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})    
add_executable(database_test database_test.cpp)
target_link_libraries(database_test ${GTEST_LIBRARIES} database)
target_link_libraries(database_test mysqlcppconn)
target_compile_features(database_test PRIVATE cxx_range_for)  
