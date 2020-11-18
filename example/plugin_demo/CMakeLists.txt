cmake_minimum_required(VERSION 2.4)

project(plugin_demo)

include_directories(../../build/include)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(VAS_PLUGIN_DEMO_NAME plugin_demod)
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    set(VAS_PLUGIN_DEMO_NAME plugin_demo)
else()
endif()

add_library(${VAS_PLUGIN_DEMO_NAME} SHARED ./plugin_demo.cpp ./demo.cpp)
