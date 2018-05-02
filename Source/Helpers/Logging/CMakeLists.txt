cmake_minimum_required(VERSION 3.10)

project(logger)

# headers

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/LogDefines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Times.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ScopeGuard.hpp
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Times.cpp
)

# project

add_library(${PROJECT_NAME}
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
