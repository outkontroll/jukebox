#include "AlbumStepCalculator.h"

using namespace jukebox::gui;

int AlbumStepCalculator::getNextVisibleAlbumsId(int currentVisibleAlbumsId, bool increase) const
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
            const int diff = albumSize % albumIndexStep;
            const int step = (diff == 0) ? albumIndexStep - 1 : diff - 1;
            currentVisibleAlbumsId = albumSize - step;
        }
        else
        {
            currentVisibleAlbumsId -= albumIndexStep;
        }
    }

    return currentVisibleAlbumsId;
}

int AlbumStepCalculator::getNextSelectedAlbumId(int currentSelectedAlbumId, bool increase) const
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

int AlbumStepCalculator::getNextSelectedAlbumIdOnSamePage(int visibleAlbumId, int currentSelectedAlbumId) const
{
    ++currentSelectedAlbumId;
    if(currentSelectedAlbumId >= visibleAlbumId + albumIndexStep ||
       currentSelectedAlbumId > albumSize)
    {
        currentSelectedAlbumId = visibleAlbumId;
    }
    return currentSelectedAlbumId;
}

bool AlbumStepCalculator::shouldStepVisibleAlbums(int visibleAlbumsId, int selectedAlbumId, bool increase) const
{
    return (increase && ((selectedAlbumId == visibleAlbumsId + albumIndexStep) ||
                        (selectedAlbumId == 1 && visibleAlbumsId + albumIndexStep > albumSize))) ||
           (!increase && ((selectedAlbumId < visibleAlbumsId) ||
                        (selectedAlbumId == albumSize && visibleAlbumsId == 1)));
}

int SongStepCalculator::getNextSelectedSongIndex(int songCount, int selectedSongIndex) const
{
    ++selectedSongIndex;
    if(selectedSongIndex >= songCount)
        selectedSongIndex = 0;

    return selectedSongIndex;
}
