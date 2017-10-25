#include "SingleAlbumCanvas.h"

using namespace jukebox::gui;
using namespace juce;

SingleAlbumCanvas::SingleAlbumCanvas()
{

}

void SingleAlbumCanvas::paint(Graphics& g)
{
    //TODO just for testing purposes
    g.setColour(Colours::aqua);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    if(image.isValid())
    {
        g.drawImage(image,
                    calculateImagePlace(),
                    RectanglePlacement::stretchToFit);
    }
}

void SingleAlbumCanvas::loadImage(const juce::String& imagePath)
{
    image = ImageFileFormat::loadFrom(File::File(imagePath));
}

Rectangle<float> SingleAlbumCanvas::calculateImagePlace() const
{
    const float width = static_cast<float>(getWidth() / 2);
    const float height = width;
    const float yPosition = (getHeight() - height) / 2;
    return {0, yPosition, width, height};
}
