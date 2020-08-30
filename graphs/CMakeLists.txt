cmake_minimum_required(VERSION 3.0.0)
project(graphs VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
include(CTest)
enable_testing()

add_executable(Graph graph.h graph.cpp heap.h heap.cpp binary_search_tree.h binary_search_tree.cpp hash_set.h hash_set.cpp main.cpp)
add_executable(GraphTest graph.h graph.cpp graph_test.cpp)
add_executable(HeapTest heap.h heap.cpp heap_test.cpp)
add_executable(BinarySearchTreeTest binary_search_tree.h binary_search_tree.cpp binary_search_tree_test.cpp)
add_executable(HashSetTest hash_set.h hash_set.cpp hash_set_test.cpp)

add_test(NAME GTest COMMAND GraphTest)
add_test(NAME HTest COMMAND HeapTest)
add_test(NAME BSTTest COMMAND BinarySearchTreeTest)
add_test(NAME HSSTest COMMAND HashSetTest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)