# cmake parameters
# cmake agrs: -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# cmake

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# project

project(music_jukebox)

# target platform

if(NOT TARGET_PLATFORM)
    if(WIN32)
        set(TARGET_PLATFORM "Windows")
    else()
        set(TARGET_PLATFORM "Linux")
    endif()
endif()

# compiler

MESSAGE( STATUS "** CMAKE_C_COMPILER : ${CMAKE_C_COMPILER}" )
MESSAGE( STATUS "** CMAKE_CXX_COMPILER : ${CMAKE_CXX_COMPILER}" )

#set(CMAKE_VERBOSE_MAKEFILE ON)

# compiler flags

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if(TARGET_PLATFORM STREQUAL "Linux")      #TODO: remove this
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -fPIC")
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

# headers

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Base/Application.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Base/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Base/Application.cpp
)

# executable

add_executable(music_jukebox ${HEADER_SOURCES} ${CPP_SOURCES})

# includes

set(INTERFACE_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Interfaces
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Base
    ${INTERFACE_DIRECTORY}
    ${JUCE_DIRECTORY}
    ${JUCE_MODULE_DIRECTORY}
    #TODO remove these after classloader:
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Extensions/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Helpers
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Helpers/Signaling
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Helpers/Logging
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Extensions/Gui
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Extensions/CreditManager
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Extensions/MusicPlayer
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Extensions/Statistics
)

target_include_directories(music_jukebox PRIVATE ${INCLUDE_DIRS})

# compiler features

# it is not used because it can not set globally
#target_compile_features(music_jukebox PUBLIC ${CPP_COMPILER_FEATURES})

# projects

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Extensions ${PROJECT_BINARY_DIR}/Source/Extensions)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Components ${PROJECT_BINARY_DIR}/Source/Components)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Helpers ${PROJECT_BINARY_DIR}/Source/Helpers)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Extensions ${PROJECT_BINARY_DIR}/Source/Extensions)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Juce ${PROJECT_BINARY_DIR}/Source/Juce)   #Juce

target_link_libraries(music_jukebox PUBLIC logger project_juce core gui creditManager musicPlayer statistics)
