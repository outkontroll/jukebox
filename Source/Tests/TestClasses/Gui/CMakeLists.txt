cmake_minimum_required(VERSION 3.10)

project(gui_test)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/integrationtest_Gui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GuiTester.h
    ${HELPERCLASSES_DIR}/Compounds/MainComponentMock.h
    ${JUCE_EVENTLOOP_RUNNER}
)

# project

add_executable(${PROJECT_NAME}
    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Gui
    ${SOURCE_DIR}/Extensions/Gui/Components
    ${SOURCE_DIR}/Extensions/Gui/Resources
    ${HELPERCLASSES_DIR}
    ${HELPERCLASSES_DIR}/Compounds
    ${TESTING_INCLUDE_DIRS}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
		      gui
                      songBuilder
                      helpers
                      #GTest::GTest
                      #GTest::Main
                      ${GTest}
                      ${GTestMain}
                      ${GMock}
                      ${GMockMain}
                      pthread
)

add_test(NAME gui_integration_test
         COMMAND ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
                   COMMENT "Running ${PROJECT_NAME}" VERBATIM)
