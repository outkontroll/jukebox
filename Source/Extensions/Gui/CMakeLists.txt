cmake_minimum_required(VERSION 3.10)

project(gui)

set(COMPONENTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Components)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
set(POSITIONCALCULATORS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PositionCalculators)

# headers

set(HEADER_SOURCES
    ${INTERFACE_DIRECTORY}/IGui.h
    ${INTERFACE_DIRECTORY}/ResourceId.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Gui.h
    ${RESOURCES_DIR}/ResourceString.h
    ${COMPONENTS_DIR}/MainWindow.h
    ${COMPONENTS_DIR}/MainComponent.h
    ${COMPONENTS_DIR}/ListBox.hpp
    ${COMPONENTS_DIR}/MultipleAlbumsCanvas.h
    ${COMPONENTS_DIR}/SingleAlbumCanvas.h
    ${COMPONENTS_DIR}/SetupPage.h
    ${COMPONENTS_DIR}/MusicSetupCanvas.h
    ${POSITIONCALCULATORS_DIR}/MainComponentPositionCalculator.h
    ${POSITIONCALCULATORS_DIR}/MultipleAlbumsCanvasPositionCalculator.h
    ${POSITIONCALCULATORS_DIR}/SingleAlbumPositionCalculator.h
    ${POSITIONCALCULATORS_DIR}/SetupPagePositionCalculator.h
    ${POSITIONCALCULATORS_DIR}/MusicSetupCanvasPositionCalculator.h
    ${POSITIONCALCULATORS_DIR}/AlbumStepCalculator.h
)

# sources

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Gui.cpp
    ${RESOURCES_DIR}/ResourceString.cpp
    ${COMPONENTS_DIR}/MainWindow.cpp
    ${COMPONENTS_DIR}/MainComponent.cpp
    ${COMPONENTS_DIR}/ListBoxImplementation.hpp
    ${COMPONENTS_DIR}/MultipleAlbumsCanvas.cpp
    ${COMPONENTS_DIR}/SingleAlbumCanvas.cpp
    ${COMPONENTS_DIR}/SetupPage.cpp
    ${COMPONENTS_DIR}/MusicSetupCanvas.cpp
    ${POSITIONCALCULATORS_DIR}/MainComponentPositionCalculator.cpp
    ${POSITIONCALCULATORS_DIR}/MultipleAlbumsCanvasPositionCalculator.cpp
    ${POSITIONCALCULATORS_DIR}/SingleAlbumPositionCalculator.cpp
    ${POSITIONCALCULATORS_DIR}/SetupPagePositionCalculator.cpp
    ${POSITIONCALCULATORS_DIR}/MusicSetupCanvasPositionCalculator.cpp
    ${POSITIONCALCULATORS_DIR}/AlbumStepCalculator.cpp
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
    ${POSITIONCALCULATORS_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INTERFACE_DIRECTORY})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMPL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC signals)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_JUCE} logger formaters fileSystem songBuilder std_addons jukeboxtimer password)
