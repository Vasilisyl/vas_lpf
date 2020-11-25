cmake_minimum_required(VERSION 2.4)

project(vas_lpf)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(LIBRARY_OUTPUT_PATH ./build/libs)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(VAS_LIB_NAME "vas_lpfd")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    set(VAS_LIB_NAME "vas_lpf")
else()
endif()

add_library(${VAS_LIB_NAME} ${VAS_LIB_TYPE} ./vasPluginContext.cpp ./vasVariant.cpp ./vasEventHandler.cpp ./vasServiceHandler.cpp ./vasException.cpp)
