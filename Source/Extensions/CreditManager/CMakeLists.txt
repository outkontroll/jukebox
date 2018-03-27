cmake_minimum_required(VERSION 3.10)

project(creditManager)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/ICreditManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CreditManager.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CreditManager.cpp
)

# project

add_library(creditManager
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(PUBLIC_INCLUDE_DIRS
    ${EXTENSION_PUBLIC_INCLUDE_DIRS}
)

set(IMPL_INCLUDE_DIRS
    ${EXTENSION_IMPL_INCLUDE_DIRS}
)

target_include_directories(creditManager PUBLIC ${PUBLIC_INCLUDE_DIRS})
target_include_directories(creditManager PRIVATE ${IMPL_INCLUDE_DIRS})
