cmake_minimum_required(VERSION 3.9.2)
project(Trailer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(Wt REQUIRED Wt HTTP)

add_executable(main main.cpp)

target_link_libraries(main Wt::Wt Wt::HTTP)
