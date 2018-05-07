cmake_minimum_required(VERSION 3.10)

project(std_addons_test)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_StdAddons.cpp
)

# project

add_executable(${PROJECT_NAME}
	    ${CPP_SOURCES}
)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    std_addons
    logger
    #GTest::GTest
    #GTest::Main
    ${GTest}
    ${GTestMain}
    pthread
)

add_test(NAME std_addons_unit_test
         COMMAND ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND ${PROJECT_NAME}
                   COMMENT "Running ${PROJECT_NAME}" VERBATIM)
