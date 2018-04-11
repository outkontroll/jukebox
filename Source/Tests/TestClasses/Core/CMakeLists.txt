cmake_minimum_required(VERSION 3.10)

project(core_test)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/componenttest_Core.cpp
)

# project

add_executable(${PROJECT_NAME}
               ${CPP_SOURCES}
               ${MOCK_HEADERS}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Core
    ${HELPERCLASSES_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
		      core
		      helpers
                      ${GTest}
                      ${GTestMain}
                      ${GMock}
                      ${GMockMain}
                      pthread
)

add_test(NAME core_component_test
         COMMAND ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND ./${PROJECT_NAME}
                   COMMENT "Running ${PROJECT_NAME}" VERBATIM)
