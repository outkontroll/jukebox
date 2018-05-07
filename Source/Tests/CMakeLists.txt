cmake_minimum_required(VERSION 3.10)

#TODO
#find_package(GTest REQUIRED)
#message(STATUS "GTest: ${GTEST_BOTH_LIBRARIES}")

find_library(GTest gtest PATHS ${LIBRARY_LINK_DIRS} NO_DEFAULT_PATH)
find_library(GTestMain gtest_main PATHS ${LIBRARY_LINK_DIRS} NO_DEFAULT_PATH)
set(GTestInclude ${LIBRARY_DIRECTORIES}/googletest/googletest/include)
#message(STATUS "** GTest and GTestMain: ${GTest} ${GTestMain} ${GTestInclude}")

find_library(GMock gmock PATHS ${LIBRARY_LINK_DIRS} NO_DEFAULT_PATH)
find_library(GMockMain gmock_main PATHS ${LIBRARY_LINK_DIRS} NO_DEFAULT_PATH)
set(GMockInclude ${LIBRARY_DIRECTORIES}/googletest/googlemock/include)
#message(STATUS "Path: ${LIBRARY_DIRECTORIES}")
#message( STATUS "** GMock and GMockMain: ${GMock} ${GMockMain} ${GMockInclude}" )

set(TESTING_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(TESTING_MAIN
    ${TESTING_DIR}/main.cpp
)

set(HELPERCLASSES_DIR
    ${TESTING_DIR}/HelperClasses
)

set(TESTCLASSES_DIR
    ${TESTING_DIR}/TestClasses
)

set(TESTING_INCLUDE_DIRS
#    ${GTEST_INCLUDE_DIRS}
    ${GTestInclude}
    ${GMockInclude}
)

set(MOCK_HEADERS
    ${TESTING_DIR}/HelperClasses/CreditManagerMock.h
    ${TESTING_DIR}/HelperClasses/FileSystemMock.h
    ${TESTING_DIR}/HelperClasses/GuiMock.h
    ${TESTING_DIR}/HelperClasses/MusicPlayerMock.h
    ${TESTING_DIR}/HelperClasses/SettingsMock.h
    ${TESTING_DIR}/HelperClasses/StatisticsMock.h
)

# this is needed because of the googletest libraries are generating tons of warnings
# and those should be used by find_package (and the cmakefiles modified accordingly)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -Wno-undef
        -Wno-zero-as-null-pointer-constant
        -Wno-c++98-compat-pedantic
        -Wno-missing-noreturn
        -Wno-shift-sign-overflow
        -Wno-used-but-marked-unused
        -Wno-global-constructors
        -Wno-deprecated
        -Wno-sign-conversion
    )
endif()

set(JUCE_EVENTLOOP_RUNNER
    ${HELPERCLASSES_DIR}/JuceEventLoopRunner.h
)

add_subdirectory(TestClasses/CreditManager)
add_subdirectory(TestClasses/Gui)
add_subdirectory(TestClasses/Settings)
add_subdirectory(TestClasses/Statistics)
add_subdirectory(TestClasses/Core)
add_subdirectory(TestClasses/Signaling)
add_subdirectory(TestClasses/Helpers/Logger)
