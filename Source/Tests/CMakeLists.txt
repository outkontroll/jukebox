cmake_minimum_required(VERSION 2.8)

set(TESTING_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(TESTING_INCLUDE_DIRS
    ${LIBRARY_DIRECTORIES}/googletest/googletest/include
    ${LIBRARY_DIRECTORIES}/googletest/googlemock/include
)

#set(LINK_DIRS
#    ${CMAKE_CURRENT_SOURCE_DIR}/../../googleTest
#)

#find_library(gtest
#             NAMES "gtest"
#             PATHS ${LINK_DIRS} NO_DEFAULT_PATH)

#link_directories(${LINK_DIRS})

add_subdirectory(CreditManager)
add_subdirectory(Settings)
add_subdirectory(Statistics)
#TODO: test Core functionality trough integration tests
#add_subdirectory(Core)

enable_testing()
