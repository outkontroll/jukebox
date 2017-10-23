#ifndef RESOUCRESTRING_H
#define RESOUCRESTRING_H

#include "ResourceId.h"
#include <string>

namespace jukebox { namespace gui {

const std::string UnknownError = "Unknown error";
const std::string ErrorFewCreditsSong = "Too few credits to play a song!";
const std::string ErrorFewCreditsAlbum = "Too few credits to play an album!";
const std::string ErrorDuringSongPlaying = "An unexpected error occured during playing song: ";
const std::string WarningNotPlayingSong = "Music already stopped!";

std::string getResourceStringFromId(ResourceId resourceId)
{
    switch(resourceId)
    {
    case ResourceId::ErrorFewCreditsSong: return ErrorFewCreditsSong;
    case ResourceId::ErrorFewCreditsAlbum: return ErrorFewCreditsAlbum;
    case ResourceId::ErrorDuringSongPlaying: return ErrorDuringSongPlaying;
    case ResourceId::WarningNotPlayingSong: return WarningNotPlayingSong;
    default: return UnknownError;
    }
}

}}

#endif // RESOUCRESTRING_H
