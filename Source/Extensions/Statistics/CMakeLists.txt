cmake_minimum_required(VERSION 3.10)

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

set(PUBLIC_INCLUDE_DIRS
    ${EXTENSION_PUBLIC_INCLUDE_DIRS}
)

set(IMPL_INCLUDE_DIRS
    ${EXTENSION_IMPL_INCLUDE_DIRS}
)

target_include_directories(statistics PUBLIC ${INCLUDE_DIRS})
target_include_directories(statistics PRIVATE ${IMPL_INCLUDE_DIRS})

target_link_libraries(statistics songBuilder)
