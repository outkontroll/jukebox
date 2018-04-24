#include "CreditManager.h"
#include "Logger.h"

using namespace jukebox::alternatives::creditmanager;

unsigned int CreditManagerFree::getCredits() const
{
    return 0;
}

void CreditManagerFree::coinInsert50()
{
}

void CreditManagerFree::coinInsert100()
{
}

void CreditManagerFree::coinInsert200()
{
}

bool CreditManagerFree::hasEnoughCreditsToPlaySong() const
{
    return true;
}

bool CreditManagerFree::hasEnoughCreditsToPlayAlbum() const
{
    return true;
}

bool CreditManagerFree::startPlaySong()
{
    return true;
}

bool CreditManagerFree::startPlayAlbum()
{   
    return true;
}

void CreditManagerFree::creditIncrease()
{
}

void CreditManagerFree::creditDecrease()
{
}    
