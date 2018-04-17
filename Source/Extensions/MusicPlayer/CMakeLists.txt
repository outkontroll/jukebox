cmake_minimum_required(VERSION 3.10)

project(musicPlayer)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/IMusicPlayer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MusicPlayer.h
    ${SOURCE_DIR}/Helpers/Song.h
    ${SOURCE_DIR}/Helpers/Exceptions/MusicPlayerExceptions.h
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

set(PUBLIC_INCLUDE_DIRS
    ${EXTENSION_PUBLIC_INCLUDE_DIRS}
)

set(IMPL_INCLUDE_DIRS
    ${EXTENSION_IMPL_INCLUDE_DIRS}
)

target_include_directories(musicPlayer PUBLIC ${PUBLIC_INCLUDE_DIRS})
target_include_directories(musicPlayer PRIVATE ${IMPL_INCLUDE_DIRS})
target_include_directories(musicPlayer SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

target_link_libraries(musicPlayer PUBLIC signals)
