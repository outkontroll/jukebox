# cmake parameters
# cmake agrs: -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# cmake

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# project

project(music_jukebox)

# compiler

MESSAGE( STATUS "** CMAKE_C_COMPILER : ${CMAKE_C_COMPILER}" )
MESSAGE( STATUS "** CMAKE_CXX_COMPILER : ${CMAKE_CXX_COMPILER}" )

#set(CMAKE_VERBOSE_MAKEFILE ON)

# compiler flags

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -fPIC")
    #TODO: this is for testing
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-c++98-compat-bind-to-temporary-copy -Wno-padded -Wno-exit-time-destructors -Wno-weak-vtables")
    #END TODO
    #if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    #endif()
endif()

MESSAGE( STATUS "** CMAKE_CXX_FLAGS : ${CMAKE_CXX_FLAGS}" )

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

MESSAGE( STATUS "** PROJECT_BINARY_DIR : ${PROJECT_BINARY_DIR}" )

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../${CMAKE_BUILD_TYPE} CACHE PATH "Library output path")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../${CMAKE_BUILD_TYPE} CACHE PATH "Executable output path")

MESSAGE( STATUS "** LIBRARY_OUTPUT_PATH : ${LIBRARY_OUTPUT_PATH}" )
MESSAGE( STATUS "** EXECUTABLE_OUTPUT_PATH : ${EXECUTABLE_OUTPUT_PATH}" )

MESSAGE( STATUS "** CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}" )

# juce

set(JUCE_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode
)

set(JUCE_MODULE_DIRECTORY
    ${JUCE_DIRECTORY}/modules
)

MESSAGE( STATUS "** JUCE_DIRECTORY : ${JUCE_DIRECTORY}" )

# global definitions

set(SOURCE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

set(LIBRARY_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries
)

# headers

set(HEADER_SOURCES
    ${SOURCE_DIR}/Base/Application.h
)

# sources

set(CPP_SOURCES
    ${SOURCE_DIR}/Base/main.cpp
    ${SOURCE_DIR}/Base/Application.cpp
)

# executable

add_executable(music_jukebox ${HEADER_SOURCES} ${CPP_SOURCES})

# includes

set(INTERFACE_DIRECTORY
    ${SOURCE_DIR}/Interfaces
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Base
    ${INTERFACE_DIRECTORY}
    ${JUCE_DIRECTORY}
    ${JUCE_MODULE_DIRECTORY}
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
    ${SOURCE_DIR}/Extensions/FileSystem
)

target_include_directories(music_jukebox PRIVATE ${INCLUDE_DIRS})

# compiler features

# it is not used because it can not set globally
#target_compile_features(music_jukebox PUBLIC ${CPP_COMPILER_FEATURES})

# projects

add_subdirectory(${SOURCE_DIR}/Extensions ${PROJECT_BINARY_DIR}/Source/Extensions)
add_subdirectory(${SOURCE_DIR}/Helpers ${PROJECT_BINARY_DIR}/Source/Helpers)
add_subdirectory(${SOURCE_DIR}/Juce ${PROJECT_BINARY_DIR}/Source/Juce)   #Juce
add_subdirectory(${SOURCE_DIR}/Tests)

target_link_libraries(music_jukebox PUBLIC logger project_juce core gui creditManager musicPlayer statistics songBuilder settings fileSystem)
