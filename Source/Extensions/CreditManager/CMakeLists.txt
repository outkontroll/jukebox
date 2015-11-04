cmake_minimum_required(VERSION 2.8)

project(creditManager)

# headers

set(HEADER_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/../../Interfaces/ICreditManager.h
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

set(INCLUDE_DIRS
${EXTENSION_INCLUDE_DIRS}
)

target_include_directories(creditManager PUBLIC ${INCLUDE_DIRS})
