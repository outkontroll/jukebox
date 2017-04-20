#include "MusicPlayer.h"
#include "Formaters.h"
#include "Logger.h"
#include "MusicPlayerImplementation.h"

using namespace jukebox;
using namespace jukebox::audio;

MusicPlayer::MusicPlayer() :
    pImpl(std::make_unique<MusicPlayerImplementation>())
{
}

void MusicPlayer::playSong(const std::string& song)
{
//    LOG_INFO("Playing: " << FillWithLeadingZeros(song.getAlbumNumber(), 3) << " " << FillWithLeadingZeros(song.getSongNumber(), 2));
    LOG_INFO("Playing: " << song);
    pImpl->playSong(song);
}

void MusicPlayer::stopPlaying()
{
    LOG_INFO("Stoped playing.");
    pImpl->stopPlaying();
}
