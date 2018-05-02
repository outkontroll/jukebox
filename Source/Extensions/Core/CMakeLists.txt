cmake_minimum_required(VERSION 3.10)

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

target_include_directories(core PUBLIC ${INTERFACE_DIRECTORY})

target_link_libraries(core PUBLIC signals)
target_link_libraries(core PRIVATE songBuilder logger exceptions)
