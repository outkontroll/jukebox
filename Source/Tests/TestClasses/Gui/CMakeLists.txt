cmake_minimum_required(VERSION 2.8)

project(integrationtest_Gui)

# sources

set(CPP_SOURCES
    ${TESTING_DIR}/main.cpp
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
		      #helpers
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest.a
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest_main.a
                      ${LIBRARY_DIRECTORIES}/Libs/libgmock.a
                      ${LIBRARY_DIRECTORIES}/Libs/libgmock_main.a
		      pthread
)

enable_testing()
add_test(MyTest integrationtest_Gui)

add_custom_command(TARGET integrationtest_Gui
                   POST_BUILD
                   COMMAND ${EXECUTABLE_OUTPUT_PATH}/integrationtest_Gui
                   WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
                   COMMENT "Running integrationtest_Gui" VERBATIM)
