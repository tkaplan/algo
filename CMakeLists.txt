cmake_minimum_required (VERSION 2.8)
project (Algo)

set (Algo_VERSION_MAJOR 0)
set (Algo_VERSION_MINOR 1)
set (CMAKE_CXX_COMPILER g++-4.8)
set (CMAKE_BUILD_TYPE Release)

add_definitions(
  -std=c++11
)

configure_file(
  "${PROJECT_SOURCE_DIR}/algo.h.in"
  "${PROJECT_BINARY_DIR}/algo.h"
)

include_directories(NetworkModule/CrawlTickers)

add_subdirectory(NetworkModule/CrawlTickers)

add_executable(Run run.cpp)