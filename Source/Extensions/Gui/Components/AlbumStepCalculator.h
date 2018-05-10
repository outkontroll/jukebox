#ifndef ALBUMSTEPCALCULATOR_H
#define ALBUMSTEPCALCULATOR_H

namespace jukebox { namespace gui {

struct AlbumStepCalculator
{
    const unsigned long albumSize;
    const unsigned long albumIndexStep;

    unsigned long getNextVisibleAlbumsId(unsigned long currentVisibleAlbumsId, bool increase) const;
    unsigned long getNextSelectedAlbumId(unsigned long currentSelectedAlbumId, bool increase) const;
    unsigned long getNextSelectedAlbumIdOnSamePage(unsigned long visibleAlbumId, unsigned long currentSelectedAlbumId) const;
    bool shouldStepVisibleAlbums(unsigned long visibleAlbumsId, unsigned long selectedAlbumId, bool increase) const;
};

struct SongStepCalculator
{
    unsigned long getNextSelectedSongIndex(unsigned long songCount, unsigned long selectedSongIndex) const;
};

}}

#endif //ALBUMSTEPCALCULATOR_H
