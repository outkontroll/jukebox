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

add_library(${PROJECT_NAME}
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_DIRECTORY})

target_link_libraries(${PROJECT_NAME} PRIVATE song jukeboxtimer datetime)
