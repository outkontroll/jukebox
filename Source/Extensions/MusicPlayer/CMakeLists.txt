cmake_minimum_required(VERSION 3.10)

project(musicPlayer)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/IMusicPlayer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicPlayer.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicPlayer.cpp
)

# project

add_library(musicPlayer
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_DIRECTORY})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC signals song)
target_link_libraries(${PROJECT_NAME} PRIVATE logger exceptions)
