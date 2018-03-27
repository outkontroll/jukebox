cmake_minimum_required(VERSION 3.10)

project(unittest_CreditManager)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
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
                      #GTest::GTest
                      #GTest::Main
                      ${GTest}
                      ${GTestMain}
                      pthread
)

add_test(MyTest unittest_CreditManager)

add_custom_command(TARGET unittest_CreditManager
                   POST_BUILD
                   COMMAND ./unittest_CreditManager
                   COMMENT "Running unittest_CreditManager" VERBATIM)
