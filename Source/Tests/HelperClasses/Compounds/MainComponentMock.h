#ifndef MAINCOMPONENTMOCK_H
#define MAINCOMPONENTMOCK_H

#include "MainComponent.h"
#include "gmock/gmock.h"

struct MainComponentMock : public juce::MainComponent
{
    MainComponentMock()
        : MainComponent(true)
    {
        //TODO
    }
};

#endif // MAINCOMPONENTMOCK_H
