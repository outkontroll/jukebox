cmake_minimum_required(VERSION 3.10)

project(componenttest_Core)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
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
                      ${GTest}
                      ${GTestMain}
                      ${GMock}
                      ${GMockMain}
                      pthread
)

enable_testing()
add_test(MyTest componenttest_Core)

add_custom_command(TARGET componenttest_Core
                   POST_BUILD
                   COMMAND ./componenttest_Core
                   COMMENT "Running componenttest_Core" VERBATIM)
