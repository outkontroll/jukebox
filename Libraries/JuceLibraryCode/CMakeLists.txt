cmake_minimum_required(VERSION 3.10)

project(project_juce)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_library(RT rt)
find_library(DL dl)
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)
find_package(Freetype REQUIRED)

if(MSVC)
    #add_compile_options()
else()
    add_compile_options(-g -fPIC)
    #set(CMAKE_CXX_FLAGS "-g -fPIC")
endif()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(JUCE_LIBRARIES
    ${RT}
    ${DL}
    ${X11_LIBRARIES}
    ${FREETYPE_LIBRARIES}
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    #${JUCE_MODULE_DIRECTORY}
    ${FREETYPE_INCLUDE_DIRS}
)

set(JUCE_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_audio_basics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_audio_devices.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_audio_formats.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_audio_processors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_audio_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include_juce_cryptography.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_data_structures.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_events.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_graphics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_gui_basics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/juce_gui_extra.cpp
)

add_library(project_juce
            SHARED
            ${JUCE_SOURCE}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(project_juce SYSTEM PRIVATE ${INCLUDE_DIRS})

target_link_libraries(project_juce PUBLIC ${JUCE_LIBRARIES})
target_link_libraries(project_juce PUBLIC Threads::Threads asound)
