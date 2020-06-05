# cmake agrs: -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
# OR
# cmake agrs: -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
# test coverages: -DTEST_COVERAGE=ON


# cmake

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# project

project(music_jukebox)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

#set(CMAKE_VERBOSE_MAKEFILE ON)

# compiler flags

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-g -Wall -Wextra -Werror -fPIC)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-Weverything
                            -Wno-c++98-compat #multiple
                            -Wno-padded #multiple
                            -Wno-weak-vtables #multiple
                            -Wno-exit-time-destructors #logger
                            -Wno-reserved-id-macro #maincomponent
                            -Wno-extra-semi-stmt
        )
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND
   TEST_COVERAGE)
        set(GENERATE_TEST_COVERAGE ON CACHE BOOL "Generate test coverage information" FORCE)
        include(CodeCoverage)
        APPEND_COVERAGE_COMPILER_FLAGS()
        set(COVERAGE_EXCLUDES '.git/*' 'CMakeModules/*' 'Libraries/*' '*/7/*' 'nlohmann/*')
elseif(TEST_COVERAGE)
    message(WARNING "Code coverage for ${CMAKE_CXX_COMPILER_ID} is not supported!")
endif()

# compiler features

#message("Your C++ compiler supports these C++ features:")
#foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
#    message("${i}")
#endforeach()

# build architecture

if("${CMAKE_SIZEOF_VOID_P}" EQUAL 4)
    set(BUILD_ARCHITECTURE "32bit")
else()
    set(BUILD_ARCHITECTURE "64bit")
endif()

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

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Base
    ${SOURCE_DIR}/Extensions/Core
    ${SOURCE_DIR}/Extensions/CreditManager
    ${SOURCE_DIR}/Extensions/FileSystem
    ${SOURCE_DIR}/Extensions/Gui
    ${SOURCE_DIR}/Extensions/MusicPlayer
    ${SOURCE_DIR}/Extensions/Settings
    ${SOURCE_DIR}/Extensions/Statistics
)

set(JUCE_INCLUDE_DIRS
    ${JUCE_DIRECTORY}
    ${JUCE_MODULE_DIRECTORY}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

# compiler features

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${PROJECT_JUCE}
    logger
    core
    gui
    creditManager
    noCredits
    musicPlayer
    statistics
    settings
    fileSystem
    signals
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wno-cast-qual
)

# testing

enable_testing()

# projects

add_subdirectory(${SOURCE_DIR}/Extensions)
add_subdirectory(${SOURCE_DIR}/Helpers)
add_subdirectory(${SOURCE_DIR}/Tests)

# code coverage

if(GENERATE_TEST_COVERAGE)
    setup_target_for_coverage_lcov(NAME code_coverage
                                   EXECUTABLE ctest -Q
                                   DEPENDENCIES core_test
                                           creditManager_test
                                           gui_test_integration
                                           gui_test_unit
                                           settings_test
                                           statistics_test
                                           logger_test
                                           std_addons_test
                                           music_jukebox
                                   EXCLUDE ${JUCE_INCLUDE_DIRS}/*
                                            Libraries/*
                                            /usr/*
                             )
endif()
