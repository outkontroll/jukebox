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
    MOCK_METHOD2(loadMultipleAlbums, void(const std::vector<jukebox::audio::AlbumInfo>&, unsigned int));
    MOCK_METHOD2(loadSingleAlbum, void(const std::vector<jukebox::audio::AlbumInfo>&, unsigned int));
    MOCK_METHOD1(setMusicDirectory, void(const std::string&));
    MOCK_METHOD1(setTimeToPlayASong, void(int));
    MOCK_METHOD1(setTimeToSaveInsertedCoins, void(int));
    MOCK_METHOD0(switchBetweenUserModes, void());
    MOCK_METHOD0(switchBetweenAlbumViews, void());
    MOCK_METHOD0(switchBetweenAdministratorViews, void());
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
