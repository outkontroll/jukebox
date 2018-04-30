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

set(PUBLIC_INCLUDE_DIRS
    ${EXTENSION_PUBLIC_INCLUDE_DIRS}
)

set(IMPL_INCLUDE_DIRS
    ${EXTENSION_IMPL_INCLUDE_DIRS}
)

target_include_directories(fileSystem PUBLIC ${PUBLIC_INCLUDE_DIRS})
target_include_directories(fileSystem PRIVATE ${IMPL_INCLUDE_DIRS})
target_include_directories(fileSystem SYSTEM PUBLIC ${JUCE_INCLUDE_DIRS})

target_link_libraries(fileSystem PRIVATE ${PROJECT_JUCE} std_addons)
