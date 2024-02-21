cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME bigint)

project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)


add_executable(bigint main.cpp big_int.cpp big_int.hpp)