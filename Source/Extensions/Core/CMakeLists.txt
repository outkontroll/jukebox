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

set(PUBLIC_INCLUDE_DIRS
    ${EXTENSION_PUBLIC_INCLUDE_DIRS}
)

set(IMPL_INCLUDE_DIRS
    ${EXTENSION_IMPL_INCLUDE_DIRS}
)

target_include_directories(core PUBLIC ${PUBLIC_INCLUDE_DIRS})
target_include_directories(core PUBLIC ${IMPL_INCLUDE_DIRS})

target_link_libraries(core songBuilder helpers)
