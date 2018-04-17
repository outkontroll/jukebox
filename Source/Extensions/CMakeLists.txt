cmake_minimum_required(VERSION 3.10)

set(EXTENSION_PUBLIC_INCLUDE_DIRS
    ${INTERFACE_DIRECTORY}
    ${SOURCE_DIR}/Helpers
    ${SOURCE_DIR}/Helpers/Signaling
)

set(EXTENSION_IMPL_INCLUDE_DIRS
    ${SOURCE_DIR}/Helpers/Logging
    ${SOURCE_DIR}/Helpers/Exceptions
    ${SOURCE_DIR}/Helpers/SongBuilder
)

add_subdirectory(Core)
add_subdirectory(CreditManager)
add_subdirectory(FileSystem)
add_subdirectory(Gui)
add_subdirectory(MusicPlayer)
add_subdirectory(Statistics)
add_subdirectory(Settings)
