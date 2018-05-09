#include "AlbumStepCalculator.h"

using namespace jukebox::gui;

unsigned long AlbumStepCalculator::getNextVisibleAlbumsId(unsigned long currentVisibleAlbumsId, bool increase) const
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
            const unsigned long diff = albumSize % albumIndexStep;
            const unsigned long step = (diff == 0) ? albumIndexStep - 1 : diff - 1;
            currentVisibleAlbumsId = albumSize - step;
        }
        else
        {
            currentVisibleAlbumsId -= albumIndexStep;
        }
    }

    return currentVisibleAlbumsId;
}

unsigned long AlbumStepCalculator::getNextSelectedAlbumId(unsigned long currentSelectedAlbumId, bool increase) const
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

unsigned long AlbumStepCalculator::getNextSelectedAlbumIdOnSamePage(unsigned long visibleAlbumId, unsigned long currentSelectedAlbumId) const
{
    ++currentSelectedAlbumId;
    if(currentSelectedAlbumId >= visibleAlbumId + albumIndexStep ||
       currentSelectedAlbumId > albumSize)
    {
        currentSelectedAlbumId = visibleAlbumId;
    }
    return currentSelectedAlbumId;
}

unsigned long SongStepCalculator::getNextSelectedSongIndex(unsigned long songCount, unsigned long selectedSongIndex) const
{
    ++selectedSongIndex;
    if(selectedSongIndex >= songCount)
        selectedSongIndex = 0;

    return selectedSongIndex;
}
