cmake_minimum_required(VERSION 3.10)

project(songBuilder)

# headers

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/SongBuilder.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/SongBuilder.cpp
)

# project

add_library(${PROJECT_NAME}
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(PUBLIC_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set(PRIVATE_INCLUDE_DIRS
    ${INTERFACE_DIRECTORY}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE formaters)
