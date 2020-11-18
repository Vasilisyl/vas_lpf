cmake_minimum_required(VERSION 2.4)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/plugins/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/exec/)

add_subdirectory(plugin_demo)
add_subdirectory(plugin_test)
add_subdirectory(example_main)