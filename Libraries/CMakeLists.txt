cmake_minimum_required(VERSION 3.10)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs)

file(MAKE_DIRECTORY ${LIB_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})

add_subdirectory(googletest)
add_subdirectory(JuceLibraryCode)
