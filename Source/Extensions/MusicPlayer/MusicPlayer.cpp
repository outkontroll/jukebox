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
    //std::cout << "Playing: " << LeadingZeroConverter(song.getAlbum(), 3) << " " << LeadingZeroConverter(song.getSong(), 2) << std::endl;
    std::cout << "Playing: " << song.getAlbum() << " " << song.getSong() << std::endl;
}

void MusicPlayer::playAlbum(Song album)
{
    //std::cout << "Playing: " << LeadingZeroConverter(album.getAlbum(), 3) << std::endl;
    std::cout << "Playing: " << album.getAlbum() << std::endl;
}
