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

add_library(fileSystem
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

target_include_directories(fileSystem PUBLIC ${INTERFACE_DIRECTORY})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

target_link_libraries(fileSystem PRIVATE ${PROJECT_JUCE} logger formaters std_addons song)
