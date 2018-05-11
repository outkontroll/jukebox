cmake_minimum_required(VERSION 3.10)

project(password)

find_package(nlohmann_json)

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Password.h
)

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Password.cpp
)

add_library(${PROJECT_NAME}
        STATIC
        ${HEADER_SOURCES}
        ${CPP_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_JUCE} nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)
