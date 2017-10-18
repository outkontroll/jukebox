cmake_minimum_required(VERSION 2.8)

project(integrationtest_Core)

# sources

set(CPP_SOURCES
    ${TESTING_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/integrationtest_Core.cpp
)

# project

add_executable(integrationtest_Core
	    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Core
    ${HELPERCLASSES_DIR}
)

target_include_directories(integrationtest_Core PUBLIC ${INCLUDE_DIRS}
                                         SYSTEM ${TESTING_INCLUDE_DIRS})

target_link_libraries(integrationtest_Core
		      core
		      helpers
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest.a
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest_main.a
                      ${LIBRARY_DIRECTORIES}/Libs/libgmock.a
                      ${LIBRARY_DIRECTORIES}/Libs/libgmock_main.a
		      pthread
)

enable_testing()
add_test(MyTest integrationtest_Core)

add_custom_command(TARGET integrationtest_Core
                   POST_BUILD
                   COMMAND ${EXECUTABLE_OUTPUT_PATH}/integrationtest_Core
                   WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
                   COMMENT "Running integrationtest_Core" VERBATIM)
