cmake_minimum_required(VERSION 3.10)

project(DllLoader)

find_package(Boost 1.61 REQUIRED
    COMPONENTS
    system
    filesystem
)

find_library(DL dl REQUIRED)

set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/DllLoader.hpp
)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${SRC})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

target_link_libraries(${PROJECT_NAME} INTERFACE
    Boost::boost
    Boost::system
    Boost::filesystem
    ${DL}
)

# hack to show the files in the IDE
add_custom_target(${PROJECT_NAME}_IDE SOURCES ${HEADER_SOURCES})

