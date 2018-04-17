#ifndef MAINCOMPONENTMOCK_H
#define MAINCOMPONENTMOCK_H

#include "MainComponent.h"
#include "gmock/gmock.h"

struct MainComponentMock : public juce::MainComponent
{
    MainComponentMock()
        : MainComponent(true)
    {
    }

    MOCK_METHOD1(refreshCredits, void(unsigned int));
    MOCK_METHOD1(showStatusMessage, void(const juce::String&));
    MOCK_METHOD3(loadMultipleAlbums, void(const std::string&, unsigned int, const jukebox::filesystem::IFileSystem&));
    MOCK_METHOD3(loadSingleAlbum, void(const std::string&, unsigned int, const jukebox::filesystem::IFileSystem&));
    MOCK_METHOD1(setMusicDirectory, void(const std::string&));
    MOCK_METHOD0(switchBetweenAlbumViews, void());
    MOCK_METHOD0(switchBetweenUserModeViews, void());
    MOCK_METHOD1(updateAlbumSelection, void(unsigned int));
    MOCK_METHOD1(updateSongSelection, void(unsigned int));
    MOCK_METHOD1(setCurrentUserInputNumber, void(const juce::String&));
    MOCK_METHOD1(setCurrentlyPlayedSong, void(const jukebox::audio::Song&));
    MOCK_METHOD1(enqueue, void(const jukebox::audio::Song&));
    MOCK_METHOD0(removeCurrentSong, void());
    MOCK_METHOD1(showStatistics, void(const std::string&));
    MOCK_METHOD0(prepareForExit, void());
};

#endif // MAINCOMPONENTMOCK_H
