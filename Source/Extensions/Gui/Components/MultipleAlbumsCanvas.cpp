#include "MultipleAlbumsCanvas.h"

using namespace jukebox::gui;
using namespace juce;

MultipleAlbumsCanvas::MultipleAlbumsCanvas()
{

}

void MultipleAlbumsCanvas::paint(Graphics& g)
{
    //TODO just for testing purposes
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    for(const auto& image : images)
    {
        if(image.isValid())
        {
            g.drawImage(image,
                        calculateImagePlace({1, 0}),
                        RectanglePlacement::stretchToFit);

            g.drawImage(image,
                        calculateImagePlace({0, 1}),
                        RectanglePlacement::stretchToFit);
        }
    }
}

void MultipleAlbumsCanvas::loadImage(const juce::String& imagePath)
{
    auto image = ImageFileFormat::loadFrom(File::File(imagePath));
    if(!image.isValid())
    {
        //TODO error handling
        return;
    }

    images.push_back(image);
}

Rectangle<float> MultipleAlbumsCanvas::calculateImagePlace(Position position) const
{
    const float slotWidth = static_cast<float>(getWidth() / 4);
    const float slotHeight = static_cast<float>(getHeight() / 2);
    const float imageWidth = slotWidth - 20;
    const float imageHeigth = imageWidth;
    return {slotWidth * position.x + (slotWidth - imageWidth) / 2, slotHeight * position.y + (slotHeight - imageHeigth) / 1.8f, imageWidth, imageHeigth};
}
