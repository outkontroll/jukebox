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
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_ResourceString.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_AlbumStepCalculator.cpp
)

# project

add_executable(${PROJECT_NAME}
    ${CPP_SOURCES}
)

add_executable(${PROJECT_NAME}2
    ${CPP_SOURCES_UT}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Gui
    ${SOURCE_DIR}/Extensions/Gui/Components
    ${SOURCE_DIR}/Extensions/Gui/Resources
    ${HELPERCLASSES_DIR}
    ${HELPERCLASSES_DIR}/Compounds
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS} ${JUCE_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME}2 PUBLIC ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME}2 SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS} ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    gui
    songBuilder
    logger
    #GTest::GTest
    #GTest::Main
    ${GTest}
    ${GTestMain}
    ${GMock}
    ${GMockMain}
    pthread
)

target_link_libraries(${PROJECT_NAME}2 PRIVATE
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
    target_compile_options(${PROJECT_NAME}2 PUBLIC
        -Wno-covered-switch-default
        -Wno-float-equal
        -Wno-missing-prototypes
    )
endif()

add_test(NAME gui_integration_test
         COMMAND ${PROJECT_NAME})

add_test(NAME gui_unit_test
         COMMAND ${PROJECT_NAME}2)

add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND ${PROJECT_NAME}
                   COMMENT "Running ${PROJECT_NAME}" VERBATIM)

add_custom_command(TARGET ${PROJECT_NAME}2
                   POST_BUILD
                   COMMAND ${PROJECT_NAME}2
                   COMMENT "Running ${PROJECT_NAME}2" VERBATIM)
