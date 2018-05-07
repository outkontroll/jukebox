cmake_minimum_required(VERSION 3.10)

project(jukeboxtimer)

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/JukeboxTimer.h
)

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/JukeboxTimer.cpp
)

add_library(${PROJECT_NAME}
        STATIC
        ${HEADER_SOURCES}
        ${CPP_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_JUCE})
