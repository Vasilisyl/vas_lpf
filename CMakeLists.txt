cmake_minimum_required(VERSION 2.4)

project(vas_lpf)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(LIBRARY_OUTPUT_PATH ./build/libs)

add_library(vas_lpf SHARED ./vasPluginContext.cpp)
