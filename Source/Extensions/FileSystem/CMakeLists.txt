cmake_minimum_required(VERSION 2.8)

project(fileSystem)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/IFileSystem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FileSystem.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/FileSystem.cpp
)

# project

add_library(fileSystem
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
    ${EXTENSION_INCLUDE_DIRS}
    ${JUCE_DIRECTORY}
    ${JUCE_MODULE_DIRECTORY}
)

target_include_directories(fileSystem PUBLIC ${INCLUDE_DIRS})

target_link_libraries(fileSystem project_juce)
