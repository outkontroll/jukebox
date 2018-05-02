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

add_library(${PROJECT_NAME}
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_DIRECTORY})

target_link_libraries(${PROJECT_NAME} PRIVATE logger)
