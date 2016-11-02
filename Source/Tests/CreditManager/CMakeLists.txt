cmake_minimum_required(VERSION 2.8)

project(unittest_CreditManager)

# sources

set(CPP_SOURCES
    ${TESTING_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_CreditManager.cpp
)

# project

add_executable(unittest_CreditManager
	    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/CreditManager
    ${TESTING_INCLUDE_DIRS}
)

target_include_directories(unittest_CreditManager PUBLIC ${INCLUDE_DIRS})

target_link_libraries(unittest_CreditManager
		      creditManager
		      helpers
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest.a
		      ${LIBRARY_DIRECTORIES}/Libs/libgtest_main.a
		      pthread
)

enable_testing()
add_test(MyTest unittest_CreditManager)

add_custom_command(TARGET unittest_CreditManager
                   POST_BUILD
                   COMMAND ${EXECUTABLE_OUTPUT_PATH}/unittest_CreditManager
                   WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
                   COMMENT "Running unittest_CreditManager" VERBATIM)
