#ifndef MAINCOMPONENTPOSITIONCALCULATOR_H
#define MAINCOMPONENTPOSITIONCALCULATOR_H

#include "JuceHeader.h"

struct MainComponentPositionCalculator
{
    MainComponentPositionCalculator(int width, int height);

    juce::Rectangle<int> getInfoCreditBounds() const;
    juce::Rectangle<int> getLblCreditsBounds() const;
    juce::Rectangle<int> getLblStatusBounds() const;
    juce::Rectangle<int> getInfoPlayQueueBounds() const;
    juce::Rectangle<int> getInfoCurrentSongBounds() const;
    juce::Rectangle<int> getTxtCurrentSongBounds() const;
    juce::Rectangle<int> getPlayQueueBounds() const;
    juce::Rectangle<int> getLblAlbumNumberBounds() const;
    juce::Rectangle<int> getLblSongNumberBounds() const;

    juce::Rectangle<int> getCanvasBounds() const;

    int getFontHeigthBig() const;
    int getFontHeigthSmall() const;

    const int width;
    const int height;

    const int canvasLeft;
    const int canvasTop;
    const int canvasWidth;
    const int canvasHeight;

    const int offsetWidth;
    const int offsetHeight;

    const int fontHeightBig;
    const int fontHeightSmall;
    const int fontWidthBig;

    const int sidePanelLeft;
    const int sidePanelTop;
    const int sidePanelWidth;

    const int statusTop;
};

#endif //MAINCOMPONENTPOSITIONCALCULATOR_H
