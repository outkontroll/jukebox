cmake_minimum_required(VERSION 2.8)

project(gui)

set(COMPONENTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Components)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/IGui.h
    ${INTERFACE_DIRECTORY}/ResourceId.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Gui.h
    ${RESOURCES_DIR}/ResourceString.h
    ${SOURCE_DIR}/Base/MainWindow.h
    ${COMPONENTS_DIR}/MainComponent.h
    ${COMPONENTS_DIR}/ListBox.hpp
    ${COMPONENTS_DIR}/MultipleAlbumsCanvas.h
    ${COMPONENTS_DIR}/SingleAlbumCanvas.h
    ${COMPONENTS_DIR}/JukeboxTimer.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Gui.cpp
    ${RESOURCES_DIR}/ResourceString.cpp
    ${SOURCE_DIR}/Base/MainWindow.cpp
    ${COMPONENTS_DIR}/MainComponent.cpp
    ${COMPONENTS_DIR}/ListBoxImplementation.hpp
    ${COMPONENTS_DIR}/MultipleAlbumsCanvas.cpp
    ${COMPONENTS_DIR}/SingleAlbumCanvas.cpp
    ${COMPONENTS_DIR}/JukeboxTimer.cpp
)

# project

add_library(gui
    STATIC
    ${HEADER_SOURCES}
    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${EXTENSION_INCLUDE_DIRS}
    ${SOURCE_DIR}/Base
    ${RESOURCES_DIR}
    ${COMPONENTS_DIR}
    ${JUCE_DIRECTORY}
)

target_include_directories(gui PUBLIC ${INCLUDE_DIRS})

target_link_libraries(gui project_juce helpers)
