cmake_minimum_required(VERSION 3.0)

project(unittest_Settings)

# sources

set(CPP_SOURCES
    ${TESTING_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_Settings.cpp
)

# project

add_executable(unittest_Settings
	    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Settings
    ${TESTING_INCLUDE_DIRS}
)

target_include_directories(unittest_Settings PUBLIC ${INCLUDE_DIRS})

target_link_libraries(unittest_Settings
		      settings
		      helpers
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest.a
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest_main.a
		      pthread
)

enable_testing()
add_test(MyTest unittest_Settings)

add_custom_command(TARGET unittest_Settings
                   POST_BUILD
                   COMMAND ${EXECUTABLE_OUTPUT_PATH}/unittest_Settings
                   WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
                   COMMENT "Running unittest_Settings" VERBATIM)
