# cmake parameters
# cmake agrs: -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# cmake

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# project

project(music_jukebox)

# compiler

message( STATUS "** CMAKE_C_COMPILER : ${CMAKE_C_COMPILER}" )
message( STATUS "** CMAKE_CXX_COMPILER : ${CMAKE_CXX_COMPILER}" )

#set(CMAKE_VERBOSE_MAKEFILE ON)

#This property is initialized by the value of the CMAKE_CXX_STANDARD variable if it is set when a target is created. ON)

# compiler flags

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -fPIC")
    #TODO: this is for testing
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-c++98-compat-bind-to-temporary-copy -Wno-padded -Wno-exit-time-destructors -Wno-weak-vtables")
    #END TODO
endif()

message( STATUS "** CMAKE_CXX_FLAGS : ${CMAKE_CXX_FLAGS}" )

# compiler features

#message("Your C++ compiler supports these C++ features:")
#foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
#    message("${i}")
#endforeach()

#set(CPP_COMPILER_FEATURES
#    cxx_auto_type
#    cxx_noexcept
#    cxx_nullptr
#    cxx_override
#)

# build architecture

if("${CMAKE_SIZEOF_VOID_P}" EQUAL 4)
    set(BUILD_ARCHITECTURE "32bit")
else()
    set(BUILD_ARCHITECTURE "64bit")
endif()

# build directories

message( STATUS "** PROJECT_BINARY_DIR : ${PROJECT_BINARY_DIR}" )

#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../${CMAKE_BUILD_TYPE} CACHE PATH "Library output path")
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../${CMAKE_BUILD_TYPE} CACHE PATH "Executable output path")

#message( STATUS "** LIBRARY_OUTPUT_PATH : ${LIBRARY_OUTPUT_PATH}" )
#message( STATUS "** EXECUTABLE_OUTPUT_PATH : ${EXECUTABLE_OUTPUT_PATH}" )

message( STATUS "** CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}" )

# global definitions

set(SOURCE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

set(LIBRARY_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries
)

set(LIBRARY_LINK_DIRS
    ${LIBRARY_DIRECTORIES}/Libs
)

# juce

set(JUCE_DIRECTORY
    ${LIBRARY_DIRECTORIES}/JuceLibraryCode
)

set(JUCE_MODULE_DIRECTORY
    ${JUCE_DIRECTORY}/modules
)

message( STATUS "** JUCE_DIRECTORY : ${JUCE_DIRECTORY}" )

# headers

set(HEADER_SOURCES
    ${SOURCE_DIR}/Base/Application.h
)

# sources

set(CPP_SOURCES
    ${SOURCE_DIR}/Base/main.cpp
    ${SOURCE_DIR}/Base/Application.cpp
)

find_library(PROJECT_JUCE project_juce ${LIBRARY_LINK_DIRS})
#TODO
#find_package(project_juce PATHS ${LIBRARY_LINK_DIRS})
#message( STATUS "** PROJECT_JUCE : ${PROJECT_JUCE}" )
#link_directories(music_jukebox PRIVATE ${LIBRARY_LINK_DIRS})

# executable

add_executable(music_jukebox ${HEADER_SOURCES} ${CPP_SOURCES})

# includes

set(INTERFACE_DIRECTORY
    ${SOURCE_DIR}/Interfaces
)

set(LOGGER_INCLUDE_DIR
    ${SOURCE_DIR}/Helpers/Logging
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Base
    ${INTERFACE_DIRECTORY}
    #TODO remove these after classloader:
    ${SOURCE_DIR}/Extensions/Core
    ${SOURCE_DIR}/Helpers
    ${SOURCE_DIR}/Helpers/Signaling
    ${SOURCE_DIR}/Helpers/Logging
    ${SOURCE_DIR}/Extensions/Gui
    ${SOURCE_DIR}/Extensions/CreditManager
    ${SOURCE_DIR}/Extensions/MusicPlayer
    ${SOURCE_DIR}/Extensions/Statistics
    ${SOURCE_DIR}/Extensions/Settings
)

set(JUCE_INCLUDE_DIRS
    ${JUCE_DIRECTORY}
    ${JUCE_MODULE_DIRECTORY}
)

target_include_directories(music_jukebox PRIVATE ${INCLUDE_DIRS})
target_include_directories(music_jukebox SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

# compiler features

# it is not used because it can not set globally
#target_compile_features(music_jukebox PUBLIC ${CPP_COMPILER_FEATURES})

# projects

add_subdirectory(${SOURCE_DIR}/Extensions ${PROJECT_BINARY_DIR}/Source/Extensions)
add_subdirectory(${SOURCE_DIR}/Helpers ${PROJECT_BINARY_DIR}/Source/Helpers)
add_subdirectory(${SOURCE_DIR}/Tests)

target_link_libraries(music_jukebox PUBLIC ${PROJECT_JUCE} logger core gui creditManager musicPlayer statistics songBuilder settings)
