FIND_LIBRARY    ( RT           rt          )
FIND_LIBRARY    ( DL           dl          )
FIND_PACKAGE    ( X11          REQUIRED    )
FIND_PACKAGE    ( Threads      REQUIRED    )
FIND_PACKAGE    ( Freetype     REQUIRED    )
INCLUDE_DIRECTORIES ( AFTER ${FREETYPE_INCLUDE_DIRS} )
SET ( JUCE_LIBRARIES ${RT} ${DL} ${X11_LIBRARIES} ${FREETYPE_LIBRARIES} )
SET ( JUCE_SOURCE
        ${CMAKE_HOME_DIRECTORY}/JuceLibraryCode/modules/juce_core/juce_core.cpp
        ${CMAKE_HOME_DIRECTORY}/JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
        ${CMAKE_HOME_DIRECTORY}/JuceLibraryCode/modules/juce_events/juce_events.cpp
        ${CMAKE_HOME_DIRECTORY}/JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
        ${CMAKE_HOME_DIRECTORY}/JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
#        ${CMAKE_HOME_DIRECTORY}/JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
    )
ADD_LIBRARY ( project_juce STATIC ${JUCE_SOURCE} )

set(INCLUDE_DIRS
  ${CMAKE_HOME_DIRECTORY}/JuceLibraryCode
)
target_include_directories(project_juce PUBLIC ${INCLUDE_DIRS})

TARGET_LINK_LIBRARIES ( project_juce ${CMAKE_THREAD_LIBS_INIT} ${JUCE_LIBRARIES} )
