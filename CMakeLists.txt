cmake_minimum_required(VERSION 3.17)
project(ternary)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g)

add_executable(ternary main.cpp ternary_tree.cpp ternary_tree.h ternary_node.h binary_tree.cpp binary_tree.h binary_node.h exceptions.h ternary_app.cpp ternary_app.h)
