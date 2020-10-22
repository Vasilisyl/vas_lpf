cmake_minimum_required(VERSION 2.4)

project(plugin_test)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(LIBRARY_OUTPUT_PATH ./build)

add_library(plugin_test SHARED ./plugin_test.cpp ./test.cpp)
