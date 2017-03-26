cmake_minimum_required(VERSION 2.8)

add_subdirectory(Logging)

project(helpers)

# headers

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Formaters.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FileSystem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ScopeGuard.hpp
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Formaters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FileSystem.cpp
)

# project

add_library(helpers
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging/
)

target_include_directories(helpers PUBLIC ${INCLUDE_DIRS})

target_link_libraries(helpers logger)
