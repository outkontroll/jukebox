cmake_minimum_required(VERSION 2.8)

project(unittest_Core)

# sources

set(CPP_SOURCES
    ${TESTING_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_Core.cpp
)

# project

add_executable(unittest_Core
	    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Core
    ${HELPERCLASSES_DIR}
)

target_include_directories(unittest_Core PUBLIC ${INCLUDE_DIRS}
                                         SYSTEM ${TESTING_INCLUDE_DIRS})

target_link_libraries(unittest_Core
		      core
		      helpers
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest.a
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest_main.a
                      ${LIBRARY_DIRECTORIES}/Libs/libgmock.a
                      ${LIBRARY_DIRECTORIES}/Libs/libgmock_main.a
		      pthread
)

enable_testing()
add_test(MyTest unittest_Core)

add_custom_command(TARGET unittest_Core
                   POST_BUILD
                   COMMAND ${EXECUTABLE_OUTPUT_PATH}/unittest_Core
                   WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
                   COMMENT "Running unittest_Core" VERBATIM)
