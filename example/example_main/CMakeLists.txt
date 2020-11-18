cmake_minimum_required(VERSION 2.4)

project(example)

# include_directories(../../build/include)
include_directories(../../)

find_library(VAS_LIBPATH vas_lpf ${PROJECT_SOURCE_DIR}/../../build/libs)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(VAS_EXAMPLE_NAME exampled)
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    set(VAS_EXAMPLE_NAME example)
else()
endif()

add_executable(${VAS_EXAMPLE_NAME} ./main.cpp)

target_link_libraries(${VAS_EXAMPLE_NAME} ${VAS_LIBPATH} dl)
