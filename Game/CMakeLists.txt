cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(HonoursProject)
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
add_executable(HonoursProject ${SOURCE_FILES})

