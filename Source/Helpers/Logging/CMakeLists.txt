cmake_minimum_required(VERSION 2.8)

project(logger)

# headers

set(HEADER_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/LogDefines.h
${CMAKE_CURRENT_SOURCE_DIR}/Logger.h
${CMAKE_CURRENT_SOURCE_DIR}/../Times.h
)

# sources

set(CPP_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../Times.cpp
)

# project

add_library(logger
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_include_directories(logger PUBLIC ${INCLUDE_DIRS})
