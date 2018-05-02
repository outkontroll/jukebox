cmake_minimum_required(VERSION 3.10)

project(statistics_test)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_Statistics.cpp
)

# project

add_executable(${PROJECT_NAME}
    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Statistics
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    statistics
    song
    logger
    ${GTest}
    ${GTestMain}
    pthread
)

add_test(NAME statistics_unit_test
         COMMAND ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND ${PROJECT_NAME}
                   COMMENT "Running ${PROJECT_NAME}" VERBATIM)
