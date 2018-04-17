cmake_minimum_required(VERSION 3.10)

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

set(PUBLIC_INCLUDE_DIRS
    ${EXTENSION_PUBLIC_INCLUDE_DIRS}
)

set(IMPL_INCLUDE_DIRS
    ${EXTENSION_IMPL_INCLUDE_DIRS}
)

target_include_directories(settings PUBLIC ${PUBLIC_INCLUDE_DIRS})
target_include_directories(settings PRIVATE ${IMPL_INCLUDE_DIRS})
