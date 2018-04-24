cmake_minimum_required(VERSION 3.10)

project(creditManagerFree_test)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_CreditManager.cpp
)

# project

add_executable(${PROJECT_NAME}
	    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Alternatives/CreditManager
    ${INTERFACE_DIRECTORY}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${TESTING_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
                      #creditManagerFree
                      DllLoader
		      helpers
                      #GTest::GTest
                      #GTest::Main
                      ${GTest}
                      ${GTestMain}
                      pthread
)

add_test(NAME creditManagerFree_unit_test
         COMMAND ${PROJECT_NAME})

#add_custom_command(TARGET ${PROJECT_NAME}
#                   POST_BUILD
#                   COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
#                   COMMENT "Running ${PROJECT_NAME}" VERBATIM)
