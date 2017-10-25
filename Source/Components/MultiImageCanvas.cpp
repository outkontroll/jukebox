#include "MultiImageCanvas.h"

using namespace jukebox::gui;
using namespace juce;

MultiImageCanvas::MultiImageCanvas()
{

}

void MultiImageCanvas::paint(Graphics& g)
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

void MultiImageCanvas::loadImage(const juce::String& imagePath)
{
    auto image = ImageFileFormat::loadFrom(File::File(imagePath));
    if(!image.isValid())
    {
        //TODO error handling
        return;
    }

    images.push_back(image);
}

Rectangle<float> MultiImageCanvas::calculateImagePlace(Position position) const
{
    const float width = static_cast<float>(getWidth() / 3);
    const float height = static_cast<float>(getHeight() / 3);
    return {width * position.x, height * position.y, width, height};
}
