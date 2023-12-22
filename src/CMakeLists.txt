cmake_minimum_required(VERSION 3.10)
project(OS_1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(parent parent.cpp)
add_executable(child child.cpp)
