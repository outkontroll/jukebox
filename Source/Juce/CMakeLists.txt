cmake_minimum_required(VERSION 2.8)

project(project_juce)

FIND_LIBRARY    ( RT           rt          )
FIND_LIBRARY    ( DL           dl          )
FIND_PACKAGE    ( X11          REQUIRED    )
FIND_PACKAGE    ( Threads      REQUIRED    )
FIND_PACKAGE    ( Freetype     REQUIRED    )

INCLUDE_DIRECTORIES ( AFTER ${FREETYPE_INCLUDE_DIRS} )
SET ( JUCE_LIBRARIES ${RT} ${DL} ${X11_LIBRARIES} ${FREETYPE_LIBRARIES} )
SET ( JUCE_SOURCE
        ${JUCE_DIRECTORY}/juce_core.cpp
        ${JUCE_DIRECTORY}/juce_data_structures.cpp
        ${JUCE_DIRECTORY}/juce_events.cpp
        ${JUCE_DIRECTORY}/juce_graphics.cpp
        ${JUCE_DIRECTORY}/juce_gui_basics.cpp
#        ${JUCE_DIRECTORY}/juce_gui_extra.cpp
        ${JUCE_DIRECTORY}/juce_audio_basics.cpp
        ${JUCE_DIRECTORY}/juce_audio_formats.cpp
    )
ADD_LIBRARY( project_juce
             STATIC
             ${JUCE_SOURCE}
)

set(INCLUDE_DIRS
    ${JUCE_DIRECTORY}
    ${JUCE_MODULE_DIRECTORY}
)

target_include_directories(project_juce PUBLIC ${INCLUDE_DIRS})

TARGET_LINK_LIBRARIES ( project_juce ${CMAKE_THREAD_LIBS_INIT} ${JUCE_LIBRARIES} )
