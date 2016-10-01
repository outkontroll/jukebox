cmake_minimum_required(VERSION 2.8)

set(EXTENSION_INCLUDE_DIRS
${INTERFACE_DIRECTORY}
${CMAKE_CURRENT_SOURCE_DIR}/../Helpers/
${CMAKE_CURRENT_SOURCE_DIR}/../Helpers/Logging/
${CMAKE_CURRENT_SOURCE_DIR}/../Helpers/Signaling/
)

add_subdirectory(Core)
add_subdirectory(CreditManager)
add_subdirectory(Gui)
add_subdirectory(MusicPlayer)
add_subdirectory(Statistics)
