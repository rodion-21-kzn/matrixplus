cmake_minimum_required(VERSION 3.25)
project(matrixplus)

set(CMAKE_CXX_STANDARD 17)

add_executable(matrixplus s21_matrix_oop.cc s21_matrix_oop.h matrix_tests.cc)
