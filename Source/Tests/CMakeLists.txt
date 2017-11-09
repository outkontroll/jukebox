cmake_minimum_required(VERSION 2.8)

set(TESTING_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(HELPERCLASSES_DIR
    ${TESTING_DIR}/HelperClasses
)

set(TESTCLASSES_DIR
    ${TESTING_DIR}/TestClasses
)

set(TESTING_INCLUDE_DIRS
    ${LIBRARY_DIRECTORIES}/googletest/googletest/include
    ${LIBRARY_DIRECTORIES}/googletest/googlemock/include
)

set(MOCK_HEADERS
    ${TESTING_DIR}/HelperClasses/CreditManagerMock.h
    ${TESTING_DIR}/HelperClasses/GuiMock.h
    ${TESTING_DIR}/HelperClasses/MusicPlayerMock.h
    ${TESTING_DIR}/HelperClasses/SettingsMock.h
    ${TESTING_DIR}/HelperClasses/StatisticsMock.h
)

#set(LINK_DIRS
#    ${CMAKE_CURRENT_SOURCE_DIR}/../../googleTest
#)

#find_library(gtest
#             NAMES "gtest"
#             PATHS ${LINK_DIRS} NO_DEFAULT_PATH)

#link_directories(${LINK_DIRS})

add_subdirectory(TestClasses/CreditManager)
add_subdirectory(TestClasses/Gui)
add_subdirectory(TestClasses/Settings)
add_subdirectory(TestClasses/Statistics)
add_subdirectory(TestClasses/Core)

enable_testing()
