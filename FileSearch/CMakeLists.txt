cmake_minimum_required (VERSION 3.8)

project ("FileSearch")

include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable (FileSearch "src/FileSearch.cpp" "include/FileSearch.h")

# Include static library to this project
target_include_directories(FileSearch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../FileSeeker/include)
target_link_libraries(FileSearch ${CMAKE_CURRENT_SOURCE_DIR}/../FileSeeker/build/Debug/FileSeekerlib.lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FileSearch PROPERTY CXX_STANDARD 20)
endif()

