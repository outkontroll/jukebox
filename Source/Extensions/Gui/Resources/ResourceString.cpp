#include "ResourceString.h"
#include "ResourceId.h"

using namespace jukebox;
using namespace jukebox::gui;

namespace {
    const std::string UnknownError = "Unknown error";
    const std::string ErrorFewCreditsSong = "Too few credits to play a song!";
    const std::string ErrorFewCreditsAlbum = "Too few credits to play an album!";
    const std::string ErrorDuringSongPlaying = "An unexpected error occured during playing song: ";
    const std::string ErrorDuringAlbumPlaying = "An unexpected error occured during playing album: ";
    const std::string ErrorSongNotExists = "The given song is not exitsing!";
    const std::string WarningNotPlayingSong = "Music already stopped!";
    const std::string ErrorImageNotFound = "Image not available";
    const std::string Playing = "Playing";
    const std::string DefaultArtistName = "Selection Album";
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
    case ResourceId::Playing: return Playing;
    case ResourceId::DefaultArtistName: return DefaultArtistName;
    default: return UnknownError;
    }
}
