cmake_minimum_required(VERSION 3.4)
project(rubiks)

set(CMAKE_CXX_FLAGS "-std=c++11 -lpqxx -lpq")
set(INCLUDE_DIR)
set(SOURCE_FILES recurrance.cpp)
add_executable(rubiks ${SOURCE_FILES})
include_directories(${INCLUDE_DIR})
TARGET_LINK_LIBRARIES(rubiks)
