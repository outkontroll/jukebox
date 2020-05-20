cmake_minimum_required(VERSION 3.10)

project(gui_test)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/integrationtest_Gui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/integrationtest_Gui_public_interface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GuiTester.h
    ${HELPERCLASSES_DIR}/Compounds/MainComponentMock.h
    ${JUCE_EVENTLOOP_RUNNER}
)

set(CPP_SOURCES_UT
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_SingleAlbumPositionCalculator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_MultipleAlbumsPositionCalculator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_ResourceString.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_AlbumStepCalculator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_MusicSetupCanvasPositionCalculator.cpp
    ${HELPERCLASSES_DIR}/RectangleMatcher.h
    ${HELPERCLASSES_DIR}/RectangleMatcher.cpp
)

# project

add_executable(${PROJECT_NAME}_integration
    ${CPP_SOURCES}
)

add_executable(${PROJECT_NAME}_unit
    ${CPP_SOURCES_UT}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Gui
    ${SOURCE_DIR}/Extensions/Gui/Components
    ${SOURCE_DIR}/Extensions/Gui/Resources
    ${SOURCE_DIR}/Extensions/Gui/PositionCalculators
    ${HELPERCLASSES_DIR}
    ${HELPERCLASSES_DIR}/Compounds
)

target_include_directories(${PROJECT_NAME}_integration PUBLIC ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME}_integration SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS} ${JUCE_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME}_unit PUBLIC ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME}_unit SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS} ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}_integration PRIVATE
    gui
    songBuilder
    logger
    password
    #GTest::GTest
    #GTest::Main
    ${GTest}
    ${GTestMain}
    ${GMock}
    ${GMockMain}
    pthread
)

target_link_libraries(${PROJECT_NAME}_unit PRIVATE
    gui
    logger
    song
    ${GTest}
    ${GTestMain}
    ${GMock}
    ${GMockMain}
    pthread
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}_unit PUBLIC
        -Wno-covered-switch-default
        -Wno-float-equal
        -Wno-missing-prototypes
    )
endif()

add_test(NAME gui_integration_test
         COMMAND ${PROJECT_NAME}_integration)

add_test(NAME gui_unit_test
         COMMAND ${PROJECT_NAME}_unit)

#add_custom_command(TARGET ${PROJECT_NAME}
#                   POST_BUILD
#                   COMMAND ${PROJECT_NAME}
#                   COMMENT "Running ${PROJECT_NAME}" VERBATIM)

#add_custom_command(TARGET ${PROJECT_NAME}2
#                   POST_BUILD
#                   COMMAND ${PROJECT_NAME}2
#                   COMMENT "Running ${PROJECT_NAME}2" VERBATIM)
