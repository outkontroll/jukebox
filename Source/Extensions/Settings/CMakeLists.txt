cmake_minimum_required(VERSION 2.8)

project(settings)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/ISettings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Settings.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Settings.cpp
)

# project

add_library(settings
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
    ${EXTENSION_INCLUDE_DIRS}
)

target_include_directories(settings PUBLIC ${INCLUDE_DIRS})
