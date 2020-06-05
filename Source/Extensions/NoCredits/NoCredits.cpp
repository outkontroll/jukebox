#include "NoCredits.h"

using namespace jukebox::creditmanager;

int NoCredits::getCredits() const
{
    return 1;
}

void NoCredits::coinInsert50()
{    
}

void NoCredits::coinInsert100()
{
}

void NoCredits::coinInsert200()
{
}

bool NoCredits::hasEnoughCreditsToPlaySong() const
{
    return true;
}

bool NoCredits::hasEnoughCreditsToPlayAlbum() const
{
    return true;
}

bool NoCredits::startPlaySong()
{
    return true;
}

bool NoCredits::startPlayAlbum()
{
    return true;
}

void NoCredits::creditIncrease()
{
}

void NoCredits::creditDecrease()
{
}
    
