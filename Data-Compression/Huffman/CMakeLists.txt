
cmake_minimum_required(VERSION 3.10)
project(Huffman)
add_compile_options("-Wall" "-O2")
set(CMAKE_CXX_STANDARD 14)


include_directories(include)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(googletest)



