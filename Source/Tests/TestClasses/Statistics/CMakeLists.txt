cmake_minimum_required(VERSION 3.10)

project(unittest_Statistics)

# sources

set(CPP_SOURCES
    ${TESTING_MAIN}
    ${CMAKE_CURRENT_SOURCE_DIR}/unittest_Statistics.cpp
)

# project

add_executable(unittest_Statistics
	    ${CPP_SOURCES}
)

set(INCLUDE_DIRS
    ${SOURCE_DIR}/Extensions/Statistics
    ${TESTING_INCLUDE_DIRS}
)

target_include_directories(unittest_Statistics PUBLIC ${INCLUDE_DIRS})

target_link_libraries(unittest_Statistics 
		      statistics
		      helpers
                      ${GTest}
                      ${GTestMain}
                      pthread
)

enable_testing()
add_test(MyTest unittest_Statistics)

add_custom_command(TARGET unittest_Statistics
                   POST_BUILD
                   COMMAND ./unittest_Statistics
                   COMMENT "Running unittest_Statistics" VERBATIM)
