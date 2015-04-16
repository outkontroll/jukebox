/*
  ==============================================================================

    Statistics.cpp
    Created: 14 Apr 2015 11:37:11pm
    Author:  adam

  ==============================================================================
*/

#include "Statistics.h"
#include "Formaters.h"
#include <iostream>

using namespace jukebox::statistics;
using namespace jukebox::audio;

Statistics::Statistics()
{
}

Statistics::~Statistics()
{
}

void Statistics::songPlayed(Song song)
{
    ++playedSongs[song];
}

void Statistics::albumPlayed(Song album)
{
    ++playedSongs[album];
}

void Statistics::showStatistics()
{
    std::cout << std::endl << "________________" << std::endl;
    for(T_PlayedSongs::const_iterator it = playedSongs.begin(); it != playedSongs.end(); ++it)
    {
        std::cout << FillWithLeadingZeros(it->first.getAlbum(), 3) << FillWithLeadingZeros(it->first.getSong(), 2)
        << ": " << it->second << std::endl;
    }
    std::cout << "________________" << std::endl;
}
