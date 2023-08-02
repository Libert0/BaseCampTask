cmake_minimum_required (VERSION 3.8)

project ("FileSeekerlib")
set(CMAKE_CXX_STANDARD 17)   # using C++17 standart


# Create static lib from source files
add_library(FileSeekerlib STATIC src/FileSeeker.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FileSeekerlib PROPERTY CXX_STANDARD 20)
endif()

