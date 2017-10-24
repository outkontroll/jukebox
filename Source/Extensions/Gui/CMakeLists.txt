cmake_minimum_required(VERSION 2.8)

project(gui)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/IGui.h
    ${INTERFACE_DIRECTORY}/ResourceId.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Gui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ResourceString.h
    ${SOURCE_DIR}/Base/MainWindow.h
    ${SOURCE_DIR}/Components/MainComponent.h
    ${SOURCE_DIR}/Components/ListBox.hpp
    ${SOURCE_DIR}/Components/MultiImageCanvas.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Gui.cpp
    ${SOURCE_DIR}/Base/MainWindow.cpp
    ${SOURCE_DIR}/Components/MainComponent.cpp
    ${SOURCE_DIR}/Components/ListBoxImplementation.hpp
    ${SOURCE_DIR}/Components/MultiImageCanvas.cpp
)

# project

add_library(gui
    STATIC
    ${HEADER_SOURCES}
    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${EXTENSION_INCLUDE_DIRS}
    ${SOURCE_DIR}/Base/
    ${SOURCE_DIR}/Components/
    #TODO: remove this
    ${JUCE_DIRECTORY}
)

target_include_directories(gui PUBLIC ${INCLUDE_DIRS})

target_link_libraries(gui project_juce helpers)
