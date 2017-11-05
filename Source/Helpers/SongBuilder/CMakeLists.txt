cmake_minimum_required(VERSION 2.8)

project(songBuilder)

# headers

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/SongBuilder.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/SongBuilder.cpp
)

# project

add_library(songBuilder
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(songBuilder PUBLIC ${INCLUDE_DIRS})

target_link_libraries(songBuilder project_juce helpers)
