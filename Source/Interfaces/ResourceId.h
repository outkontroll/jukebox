#ifndef RESOURCEID_H
#define RESOURCEID_H

namespace jukebox {

enum class ResourceId
{
    ErrorFewCreditsSong,
    ErrorFewCreditsAlbum,
    ErrorDuringSongPlaying,
    ErrorDuringAlbumPlaying,
    ErrorSongNotExists,
    WarningNotPlayingSong,
    ErrorImageNotFound,
    ErrorNegativeNumber,
    ErrorWrongNumber,
    ErrorWrongPassword,
    Playing,
    DefaultArtistName
};

}



#endif //RESOURCEID_H
