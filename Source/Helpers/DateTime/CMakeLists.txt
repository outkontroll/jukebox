cmake_minimum_required(VERSION 3.10)

project(datetime)

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Times.h
)

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Times.cpp
)

add_library(${PROJECT_NAME}
    ${HEADER_SOURCES}
    ${CPP_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
