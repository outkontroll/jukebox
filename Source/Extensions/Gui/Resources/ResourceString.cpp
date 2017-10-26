#include "ResourceString.h"
#include "ResourceId.h"

using namespace jukebox;
using namespace jukebox::gui;

namespace {
    const std::string UnknownError = "Unknown error";
    const std::string ErrorFewCreditsSong = "Too few credits to play a song!";
    const std::string ErrorFewCreditsAlbum = "Too few credits to play an album!";
    const std::string ErrorDuringSongPlaying = "An unexpected error occured during playing song: ";
    const std::string WarningNotPlayingSong = "Music already stopped!";
    const std::string ErrorImageNotFound = "Image not available";
}

std::string Resources::getResourceStringFromId(jukebox::ResourceId resourceId)
{
    switch(resourceId)
    {
    case ResourceId::ErrorFewCreditsSong: return ErrorFewCreditsSong;
    case ResourceId::ErrorFewCreditsAlbum: return ErrorFewCreditsAlbum;
    case ResourceId::ErrorDuringSongPlaying: return ErrorDuringSongPlaying;
    case ResourceId::WarningNotPlayingSong: return WarningNotPlayingSong;
    case ResourceId::ErrorImageNotFound: return ErrorImageNotFound;
    default: return UnknownError;
    }
}
