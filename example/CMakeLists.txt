cmake_minimum_required(VERSION 2.4)

project(example)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build)

add_executable(example ./main.cpp)

link_directories(/home/wangmaobo/workspace/my.project/vasLitePluginsFramework/build/libs)

target_link_libraries(example vas_lpf dl)
