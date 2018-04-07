cmake_minimum_required(VERSION 3.10)

project(signals)

set(HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Signals.hpp
)

add_library(signals INTERFACE)
target_sources(signals INTERFACE ${HEADER_SOURCES})

target_include_directories(signals INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(signals INTERFACE cxx_std_17)

# hack to show the files in the IDE
add_custom_target(signals_IDE SOURCES ${HEADER_SOURCES})
