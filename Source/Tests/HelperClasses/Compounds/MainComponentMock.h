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

    MOCK_METHOD0(switchBetweenAlbumViews, void());
    MOCK_METHOD2(loadSingleAlbum, void(const std::string&, int));
    MOCK_METHOD2(loadMultipleAlbums, void(const std::string&, int));
    MOCK_METHOD1(updateSelection, void(int));
};

#endif // MAINCOMPONENTMOCK_H
