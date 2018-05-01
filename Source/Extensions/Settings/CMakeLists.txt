cmake_minimum_required(VERSION 3.10)

project(settings)

find_package(nlohmann_json)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/ISettings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Settings.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Settings.cpp
)

# project

add_library(${PROJECT_NAME}
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(PUBLIC_INCLUDE_DIRS
    ${EXTENSION_PUBLIC_INCLUDE_DIRS}
)

set(IMPL_INCLUDE_DIRS
    ${EXTENSION_IMPL_INCLUDE_DIRS}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMPL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
