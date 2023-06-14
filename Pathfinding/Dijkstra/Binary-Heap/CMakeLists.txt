
cmake_minimum_required(VERSION 3.10)
project(Binary-Heap)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic -O3)
include_directories(src)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(googletest)


