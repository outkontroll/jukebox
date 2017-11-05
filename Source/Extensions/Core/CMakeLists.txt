cmake_minimum_required(VERSION 2.8)

project(core)

# headers

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core.cpp
)

# project

add_library(core
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
    ${EXTENSION_INCLUDE_DIRS}
)

target_include_directories(core PUBLIC ${INCLUDE_DIRS})

target_link_libraries(core songBuilder helpers)
