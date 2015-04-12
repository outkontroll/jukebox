
# target platform

if(NOT TARGET_PLATFORM)
  if(WIN32)
    set(TARGET_PLATFORM "Windows")
  else()
    set(TARGET_PLATFORM "Linux")
  endif()
endif()

# compiler

if(TARGET_PLATFORM STREQUAL "Linux")
  set(CMAKE_C_COMPILER "gcc")
  set(CMAKE_CXX_COMPILER "g++")
endif()

# project

project(music_jukebox)

# cmake

cmake_minimum_required(VERSION 2.8)

# build architecture

if("${CMAKE_SIZEOF_VOID_P}" EQUAL 4)
  set(BUILD_ARCHITECTURE "32bit")
else()
  set(BUILD_ARCHITECTURE "64bit")
endif()

# build directories

if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Debug CACHE PATH "Library output path")
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Debug CACHE PATH "Executable output path")
elseif(CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Release CACHE PATH "Library output path")
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Release CACHE PATH "Executable output path")
else()
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Debug CACHE PATH "Library output path")
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Debug CACHE PATH "Executable output path")
endif()

# compiler flags

if(TARGET_PLATFORM STREQUAL "Linux")
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g -Wall -pipe -fPIC -fpermissive)
endif()

set(GLOBAL_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# projects

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extensions ${PROJECT_BINARY_DIR}/extensions)
