cmake_minimum_required (VERSION 2.6)
project (SSoft-2017)

file (GLOB SSoft-2017_SRC "*.c")

set (CMAKE_C_FLAGS "-g -Wall")

add_executable (SSoft-2017 ${SSoft-2017_SRC})
