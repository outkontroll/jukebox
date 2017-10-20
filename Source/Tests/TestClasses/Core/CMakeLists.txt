cmake_minimum_required(VERSION 2.8)

project(componenttest_Core)

# sources

set(CPP_SOURCES
    ${TESTING_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/componenttest_Core.cpp
)

# project

add_executable(componenttest_Core
               ${CPP_SOURCES}
               ${MOCK_HEADERS}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Core
    ${HELPERCLASSES_DIR}
)

target_include_directories(componenttest_Core PUBLIC ${INCLUDE_DIRS}
                                         SYSTEM ${TESTING_INCLUDE_DIRS})

target_link_libraries(componenttest_Core
		      core
		      helpers
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest.a
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest_main.a
                      ${LIBRARY_DIRECTORIES}/Libs/libgmock.a
                      ${LIBRARY_DIRECTORIES}/Libs/libgmock_main.a
		      pthread
)

enable_testing()
add_test(MyTest componenttest_Core)

add_custom_command(TARGET componenttest_Core
                   POST_BUILD
                   COMMAND ${EXECUTABLE_OUTPUT_PATH}/componenttest_Core
                   WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
                   COMMENT "Running componenttest_Core" VERBATIM)
