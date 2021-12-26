cmake_minimum_required(VERSION 3.16)

project(test)

SET (WT_CONNECTOR "wtfcgi" CACHE STRING "Connector used (wthttp or wtfcgi)")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")


set(LIB_SOURCE_FILES_STATIC src/connectorMysql.cpp)
add_library(connectorMysql STATIC ${LIB_SOURCE_FILES_STATIC})


set(LIB_SOURCE_FILES_STATIC src/userConnector.cpp)
add_library(userConnector STATIC ${LIB_SOURCE_FILES_STATIC})
target_link_libraries(userConnector connectorMysql)


set(LIB_SOURCE_FILES_STATIC src/filmConnector.cpp)
add_library(filmConnector STATIC ${LIB_SOURCE_FILES_STATIC})
target_link_libraries(filmConnector connectorMysql)



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")   
find_package(MySQL)
include_directories("${MYSQL_INCLUDE_DIR}")

target_link_libraries(connectorMysql ${MYSQL_LIBRARIES})
target_link_libraries(userConnector ${MYSQL_LIBRARIES})
target_link_libraries(filmConnector ${MYSQL_LIBRARIES})


set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "/usr/include/mysql-cppconn-8/jdbc")
include_directories("${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}")
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

target_link_libraries(connectorMysql mysqlcppconn)


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})    


add_executable(mysqlTest test/mysqlTest.cpp)
target_link_libraries(mysqlTest ${GTEST_LIBRARIES} connectorMysql)
target_link_libraries(mysqlTest mysqlcppconn)
 

add_executable(userTest test/userTest.cpp)
target_link_libraries(userTest ${GTEST_LIBRARIES} userConnector)
target_link_libraries(userTest mysqlcppconn)


add_executable(filmTest test/filmTest.cpp)
target_link_libraries(filmTest ${GTEST_LIBRARIES} filmConnector)
target_link_libraries(filmTest mysqlcppconn)
