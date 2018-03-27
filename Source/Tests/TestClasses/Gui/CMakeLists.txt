cmake_minimum_required(VERSION 3.10)

project(integrationtest_Gui)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/integrationtest_Gui.cpp
    ${HELPERCLASSES_DIR}/Compounds/MainComponentMock.h
    ${HELPERCLASSES_DIR}/GuiTester.h
)

# project

add_executable(integrationtest_Gui
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

target_include_directories(integrationtest_Gui PUBLIC ${INCLUDE_DIRS})

target_link_libraries(integrationtest_Gui
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

enable_testing()
add_test(MyTest integrationtest_Gui)

add_custom_command(TARGET integrationtest_Gui
                   POST_BUILD
                   COMMAND ./integrationtest_Gui
                   COMMENT "Running integrationtest_Gui" VERBATIM)
