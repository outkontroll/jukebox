#ifndef ALBUMSTEPCALCULATOR_H
#define ALBUMSTEPCALCULATOR_H

namespace jukebox { namespace gui {

struct AlbumStepCalculator
{
    const unsigned int albumSize;
    const unsigned int albumIndexStep;

    unsigned int getNextVisibleAlbumsId(unsigned int currentVisibleAlbumsId, bool increase) const;
    unsigned int getNextSelectedAlbumId(unsigned int currentSelectedAlbumId, bool increase) const;
    unsigned int getNextSelectedAlbumIdOnSamePage(unsigned int visibleAlbumId, unsigned int currentSelectedAlbumId) const;
    bool shouldStepVisibleAlbums(unsigned int visibleAlbumsId, unsigned int selectedAlbumId, bool increase) const;
};

struct SongStepCalculator
{
    unsigned int getNextSelectedSongIndex(unsigned int songCount, unsigned int selectedSongIndex) const;
};

}}

#endif //ALBUMSTEPCALCULATOR_H
