/*
  ==============================================================================

    MusicPlayer.cpp
    Created: 12 Apr 2015 3:17:00pm
    Author:  bakos

  ==============================================================================
*/

#include "MusicPlayer.h"
#include <iostream>
#include "Formaters.h"

using namespace jukebox;
using namespace jukebox::audio;

MusicPlayer::MusicPlayer()
{
}

void MusicPlayer::playSong(Song song)
{
    std::cout << "Playing: " << FillWithLeadingZeros(song.getAlbum(), 3) << " " << FillWithLeadingZeros(song.getSong(), 2) << std::endl;
}

void MusicPlayer::playAlbum(Song album)
{
    std::cout << "Playing: " << FillWithLeadingZeros(album.getAlbum(), 3) << std::endl;
}
