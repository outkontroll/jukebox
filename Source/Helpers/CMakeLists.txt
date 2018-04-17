cmake_minimum_required(VERSION 3.10)

add_subdirectory(Logging)
add_subdirectory(SongBuilder)
add_subdirectory(Signaling)

project(helpers)

# headers

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Formaters.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ScopeGuard.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/JukeboxException.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Formaters.cpp
)

# project

add_library(helpers
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging/
)

target_include_directories(helpers PRIVATE ${INCLUDE_DIRS})
target_include_directories(helpers SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

target_link_libraries(helpers logger)
