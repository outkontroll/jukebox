cmake_minimum_required(VERSION 2.8)

project(statistics)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/IStatistics.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Statistics.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Statistics.cpp
)

# project

add_library(statistics
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
    ${EXTENSION_INCLUDE_DIRS}
)

target_include_directories(statistics PUBLIC ${INCLUDE_DIRS})
