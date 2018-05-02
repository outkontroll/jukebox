cmake_minimum_required(VERSION 3.10)

project(test_Signaling)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/stest_Signaling.cpp
)

# project

add_executable(${PROJECT_NAME}
    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Settings
    ${SOURCE_DIR}/Extensions/Gui/Components
    ${HELPERCLASSES_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS} ${JUCE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    gui
    logger
    song
    ${GTest}
    ${GTestMain}
    ${GMock}
    ${GMockMain}
    pthread
)

add_test(signaling_prototype_test ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND ${PROJECT_NAME}
                   COMMENT "Running stest_Signaling" VERBATIM)
