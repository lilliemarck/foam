cmake_minimum_required(VERSION 2.8)
project(foam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Werror")

include_directories(.)

add_subdirectory(foam)
