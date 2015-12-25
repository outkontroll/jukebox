cmake_minimum_required(VERSION 2.8)

project(gui)

# headers

set(HEADER_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/../../Interfaces/IGui.h
${CMAKE_CURRENT_SOURCE_DIR}/Gui.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Base/MainWindow.h
${CMAKE_CURRENT_SOURCE_DIR}/../../Components/MainComponent.h
)

# sources

set(CPP_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/Gui.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Base/MainWindow.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../../Components/MainComponent.cpp
)

# project

add_library(gui
	    STATIC
	    ${HEADER_SOURCES}
	    ${CPP_SOURCES})

set(INCLUDE_DIRS
${EXTENSION_INCLUDE_DIRS}
${CMAKE_CURRENT_SOURCE_DIR}/../../Base/
${CMAKE_CURRENT_SOURCE_DIR}/../../Components/
#TODO: remove this
${JUCE_DIRECTORY}
)

target_include_directories(gui PUBLIC ${INCLUDE_DIRS})

target_link_libraries(gui project_juce helpers)
