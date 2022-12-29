cmake_minimum_required(VERSION 3.23)
project(hash_file)

set(CMAKE_CXX_STANDARD 23)

add_executable(hash_file src/main.cpp src/mathematics.cpp lib/mathematics.h)
