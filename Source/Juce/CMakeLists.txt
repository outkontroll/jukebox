cmake_minimum_required(VERSION 2.8)

project(project_juce)

find_library(RT rt)
find_library(DL dl)
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)
find_package(Freetype REQUIRED)

set(JUCE_LIBRARIES
    ${RT}
    ${DL}
    ${X11_LIBRARIES}
    ${FREETYPE_LIBRARIES}
)

set(JUCE_SOURCE
    ${JUCE_DIRECTORY}/juce_audio_basics.cpp
    ${JUCE_DIRECTORY}/juce_audio_devices.cpp
    ${JUCE_DIRECTORY}/juce_audio_formats.cpp
    ${JUCE_DIRECTORY}/juce_audio_processors.cpp
    ${JUCE_DIRECTORY}/juce_audio_utils.cpp
    ${JUCE_DIRECTORY}/juce_core.cpp
    ${JUCE_DIRECTORY}/juce_data_structures.cpp
    ${JUCE_DIRECTORY}/juce_events.cpp
    ${JUCE_DIRECTORY}/juce_graphics.cpp
    ${JUCE_DIRECTORY}/juce_gui_basics.cpp
    ${JUCE_DIRECTORY}/juce_gui_extra.cpp
)

add_library(project_juce
            STATIC
            ${JUCE_SOURCE}
)

set(INCLUDE_DIRS
    ${JUCE_DIRECTORY}
    ${JUCE_MODULE_DIRECTORY}
    ${FREETYPE_INCLUDE_DIRS}
)

target_include_directories(project_juce PUBLIC ${INCLUDE_DIRS})

TARGET_LINK_LIBRARIES ( project_juce ${CMAKE_THREAD_LIBS_INIT} ${JUCE_LIBRARIES} asound)
