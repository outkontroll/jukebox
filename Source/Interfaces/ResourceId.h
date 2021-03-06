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
    ErrorAlbumNotExists,
    ErrorAlbumEmpty,
    WarningNotPlayingSong,
    ErrorImageNotFound,
    ErrorNegativeNumber,
    ErrorWrongNumber,
    ErrorWrongPassword,
    ErrorDuringAlbumImport,
    Playing,
    DefaultArtistName
};

}



#endif //RESOURCEID_H
