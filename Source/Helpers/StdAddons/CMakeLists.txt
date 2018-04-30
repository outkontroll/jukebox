cmake_minimum_required(VERSION 3.10)

project(std_addons)

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/StdAddons.hpp
)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${HEADER_SOURCES})

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

# hack to show the files in the IDE
add_custom_target(${PROJECT_NAME}_IDE SOURCES ${HEADER_SOURCES})
