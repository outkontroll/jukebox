#include "ResourceString.h"
#include "ResourceId.h"

using namespace jukebox;
using namespace jukebox::gui;

namespace {
    const char* UnknownError = "Unknown error";
    const char* ErrorFewCreditsSong = "Too few credits to play a song!";
    const char* ErrorFewCreditsAlbum = "Too few credits to play an album!";
    const char* ErrorDuringSongPlaying = "An unexpected error occured during playing song: ";
    const char* ErrorDuringAlbumPlaying = "An unexpected error occured during playing album: ";
    const char* ErrorSongNotExists = "The given song is not existing!";
    const char* WarningNotPlayingSong = "Music already stopped!";
    const char* ErrorImageNotFound = "Image not available";
    const char* ErrorNegativeNumber = "Negative values are not accepted!";
    const char* Playing = "Playing";
    const char* DefaultArtistName = "Selection Album";
}

std::string Resources::getResourceStringFromId(jukebox::ResourceId resourceId)
{
    switch(resourceId)
    {
    case ResourceId::ErrorFewCreditsSong: return ErrorFewCreditsSong;
    case ResourceId::ErrorFewCreditsAlbum: return ErrorFewCreditsAlbum;
    case ResourceId::ErrorDuringSongPlaying: return ErrorDuringSongPlaying;
    case ResourceId::ErrorDuringAlbumPlaying: return ErrorDuringAlbumPlaying;
    case ResourceId::ErrorSongNotExists: return ErrorSongNotExists;
    case ResourceId::WarningNotPlayingSong: return WarningNotPlayingSong;
    case ResourceId::ErrorImageNotFound: return ErrorImageNotFound;
    case ResourceId::ErrorNegativeNumber: return ErrorNegativeNumber;
    case ResourceId::Playing: return Playing;
    case ResourceId::DefaultArtistName: return DefaultArtistName;
    }

    return UnknownError;
}
