cmake_minimum_required(VERSION 2.4)

project(example)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build)

add_executable(example ./main.cpp)

include_directories(../build/include)

find_library(VAS_LIBPATH vas_lpf ${PROJECT_SOURCE_DIR}/../build/libs)

target_link_libraries(example ${VAS_LIBPATH} dl)
