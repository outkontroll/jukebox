cmake_minimum_required(VERSION 3.10)

project(noCredits)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/ICreditManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/NoCredits.h
)

# sources

set(CPP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/NoCredits.cpp
)

# project

add_library(${PROJECT_NAME}
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_DIRECTORY} ${CMAKE_CURRENT_SOURCE_DIR})

