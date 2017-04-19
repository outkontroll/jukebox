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

void MusicPlayer::playSong(Song song)
{
    LOG_INFO("Playing: " << FillWithLeadingZeros(song.getAlbumNumber(), 3) << " " << FillWithLeadingZeros(song.getSongNumber(), 2));
    pImpl->playSong(song);
}

void MusicPlayer::playAlbum(Album album)
{
    LOG_INFO("Playing: " << FillWithLeadingZeros(album.getAlbumNumber(), 3));
    pImpl->playAlbum(album);
}

void MusicPlayer::stopPlaying()
{
    LOG_INFO("Stoped playing.");
    pImpl->stopPlaying();
}
