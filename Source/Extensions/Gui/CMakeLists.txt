cmake_minimum_required(VERSION 3.10)

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
    ${COMPONENTS_DIR}/SingleAlbumPositionCalculator.h
    ${COMPONENTS_DIR}/JukeboxTimer.h
    ${COMPONENTS_DIR}/SetupPage.h
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
    ${COMPONENTS_DIR}/SingleAlbumPositionCalculator.cpp
    ${COMPONENTS_DIR}/JukeboxTimer.cpp
    ${COMPONENTS_DIR}/SetupPage.cpp
)

# project

add_library(${PROJECT_NAME}
    STATIC
    ${HEADER_SOURCES}
    ${CPP_SOURCES}
)

set(IMPL_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOURCE_DIR}/Base
    ${RESOURCES_DIR}
    ${COMPONENTS_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_DIRECTORY})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMPL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC signals)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_JUCE} logger formaters songBuilder std_addons)
