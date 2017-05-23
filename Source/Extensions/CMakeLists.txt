cmake_minimum_required(VERSION 2.8)

set(EXTENSION_INCLUDE_DIRS
    ${INTERFACE_DIRECTORY}
    ${SOURCE_DIR}/Helpers/
    ${SOURCE_DIR}/Helpers/Logging/
    ${SOURCE_DIR}/Helpers/Signaling/
    ${SOURCE_DIR}/Helpers/Exceptions/
)

add_subdirectory(Core)
add_subdirectory(CreditManager)
add_subdirectory(Gui)
add_subdirectory(MusicPlayer)
add_subdirectory(Statistics)
add_subdirectory(Settings)
