cmake_minimum_required(VERSION 3.0.0)
project(graphs VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
include(CTest)
enable_testing()

add_executable(Graph graph.h graph.cpp main.cpp)
add_executable(GraphTest graph.h graph.cpp graph_test.cpp)

add_test(NAME GTest COMMAND GraphTest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)