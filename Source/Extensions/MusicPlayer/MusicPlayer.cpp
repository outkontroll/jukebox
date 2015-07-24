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
#include "Logger.h"

using namespace jukebox;
using namespace jukebox::audio;

void MusicPlayer::playSong(Song song)
{
    //TODO: play a song
    LOG_INFO("Playing: " << FillWithLeadingZeros(song.getAlbum(), 3) << " " << FillWithLeadingZeros(song.getSong(), 2));
}

void MusicPlayer::playAlbum(Song album)
{
    //TODO: play an album
    LOG_INFO("Playing: " << FillWithLeadingZeros(album.getAlbum(), 3));
}

void MusicPlayer::stopPlaying()
{
    LOG_INFO("Stoped playing.");
}

