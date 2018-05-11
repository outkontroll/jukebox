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

add_library(${PROJECT_NAME} ${HEADER_SOURCES} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_DIRECTORY})

target_link_libraries(${PROJECT_NAME} PUBLIC signals)
target_link_libraries(${PROJECT_NAME} PRIVATE songBuilder logger exceptions password)
