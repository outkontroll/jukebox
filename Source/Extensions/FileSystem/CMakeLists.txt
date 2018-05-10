cmake_minimum_required(VERSION 3.10)

project(fileSystem)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/IFileSystem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FileSystem.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/FileSystem.cpp
)

# project

add_library(${PROJECT_NAME} ${HEADER_SOURCES} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_DIRECTORY})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_JUCE} logger songBuilder std_addons)
