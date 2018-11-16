#ifndef ALBUMSTEPCALCULATOR_H
#define ALBUMSTEPCALCULATOR_H

namespace jukebox { namespace gui {

struct AlbumStepCalculator
{
    const int albumSize;
    const int albumIndexStep;

    int getNextVisibleAlbumsId(int currentVisibleAlbumsId, bool increase) const;
    int getNextSelectedAlbumId(int currentSelectedAlbumId, bool increase) const;
    int getNextSelectedAlbumIdOnSamePage(int visibleAlbumId, int currentSelectedAlbumId) const;
    bool shouldStepVisibleAlbums(int visibleAlbumsId, int selectedAlbumId, bool increase) const;
};

struct SongStepCalculator
{
    int getNextSelectedSongIndex(int songCount, int selectedSongIndex) const;
};

}}

#endif //ALBUMSTEPCALCULATOR_H
