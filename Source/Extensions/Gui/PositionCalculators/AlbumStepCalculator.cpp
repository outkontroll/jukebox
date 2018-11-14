#include "AlbumStepCalculator.h"

using namespace jukebox::gui;

unsigned int AlbumStepCalculator::getNextVisibleAlbumsId(unsigned int currentVisibleAlbumsId, bool increase) const
{
    if(increase)
    {
        currentVisibleAlbumsId += albumIndexStep;

        if(currentVisibleAlbumsId > albumSize)
        {
            currentVisibleAlbumsId = 1;
        }
    }
    else
    {
        if(currentVisibleAlbumsId < albumIndexStep)
        {
            const unsigned int diff = albumSize % albumIndexStep;
            const unsigned int step = (diff == 0) ? albumIndexStep - 1 : diff - 1;
            currentVisibleAlbumsId = albumSize - step;
        }
        else
        {
            currentVisibleAlbumsId -= albumIndexStep;
        }
    }

    return currentVisibleAlbumsId;
}

unsigned int AlbumStepCalculator::getNextSelectedAlbumId(unsigned int currentSelectedAlbumId, bool increase) const
{
    if(increase)
    {
        ++currentSelectedAlbumId;
        if(currentSelectedAlbumId > albumSize)
        {
            currentSelectedAlbumId = 1;
        }
    }
    else
    {
        --currentSelectedAlbumId;
        if(currentSelectedAlbumId < 1)
        {
            currentSelectedAlbumId = albumSize;
        }
    }

    return currentSelectedAlbumId;
}

unsigned int AlbumStepCalculator::getNextSelectedAlbumIdOnSamePage(unsigned int visibleAlbumId, unsigned int currentSelectedAlbumId) const
{
    ++currentSelectedAlbumId;
    if(currentSelectedAlbumId >= visibleAlbumId + albumIndexStep ||
       currentSelectedAlbumId > albumSize)
    {
        currentSelectedAlbumId = visibleAlbumId;
    }
    return currentSelectedAlbumId;
}

bool AlbumStepCalculator::shouldStepVisibleAlbums(unsigned int visibleAlbumsId, unsigned int selectedAlbumId, bool increase) const
{
    return (increase && ((selectedAlbumId == visibleAlbumsId + albumIndexStep) ||
                        (selectedAlbumId == 1 && visibleAlbumsId + albumIndexStep > albumSize))) ||
           (!increase && ((selectedAlbumId < visibleAlbumsId) ||
                        (selectedAlbumId == albumSize && visibleAlbumsId == 1)));
}

unsigned int SongStepCalculator::getNextSelectedSongIndex(unsigned int songCount, unsigned int selectedSongIndex) const
{
    ++selectedSongIndex;
    if(selectedSongIndex >= songCount)
        selectedSongIndex = 0;

    return selectedSongIndex;
}
