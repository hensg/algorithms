cmake_minimum_required(VERSION 3.16)
project(int_mult)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(int_mult
        grade_school.cpp
        grade_school.hpp
        main.cpp
        recursive_mult.cpp
        recursive_mult.hpp
        karatsuba_mult.cpp
        karatsuba_mult.hpp)
