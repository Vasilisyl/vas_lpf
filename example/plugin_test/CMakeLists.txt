cmake_minimum_required(VERSION 2.4)

project(plugin_test)

include_directories(../../build/include)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(VAS_PLUGIN_TEST_NAME plugin_testd)
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    set(VAS_PLUGIN_TEST_NAME plugin_test)
else()
endif()

add_library(${VAS_PLUGIN_TEST_NAME} SHARED ./plugin_test.cpp ./test.cpp)
