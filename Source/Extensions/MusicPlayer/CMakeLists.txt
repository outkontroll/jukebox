cmake_minimum_required(VERSION 2.8)

project(musicPlayer)

# headers

set(HEADER_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/../../Interfaces/IMusicPlayer.h
${CMAKE_CURRENT_SOURCE_DIR}/MusicPlayer.h
)

# sources

set(CPP_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/MusicPlayer.cpp
)

# project

add_library(musicPlayer
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
${EXTENSION_INCLUDE_DIRS}
${JUCE_DIRECTORY}
${JUCE_MODULE_DIRECTORY}
)

target_include_directories(musicPlayer PUBLIC ${INCLUDE_DIRS})
