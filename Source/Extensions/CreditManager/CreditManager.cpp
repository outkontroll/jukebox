/*
  ==============================================================================

    KreditManager.cpp
    Created: 16 Feb 2015 1:21:36pm
    Author:  bakos

  ==============================================================================
*/

#include "CreditManager.h"

using namespace jukebox::creditmanager;

const unsigned int CREDIT_TO_PLAY_SONG = 1;
const unsigned int CREDIT_TO_PLAY_ALBUM = 6;

CreditManager::CreditManager()
: credits(0), 
    secondCoin(false)
{
    
}

CreditManager::~CreditManager()
{
    
}

unsigned int CreditManager::getCredits() const
{
    return credits;
}

void CreditManager::coinInsert50()
{    
    if(secondCoin)
    {
        secondCoin = false;
        credits += 2;
    }
    else
    {
        secondCoin = true;
        ++credits;
    }
}

void CreditManager::coinInsert100()
{
    coinInsert50();
    coinInsert50();
}

void CreditManager::coinInsert200()
{
    coinInsert100();
    coinInsert100();
}

bool CreditManager::hasEnoughCreditsToPlaySong()
{
    return credits >= CREDIT_TO_PLAY_SONG;
}

bool CreditManager::hasEnoughCreditsToPlayAlbum()
{
    return credits >= CREDIT_TO_PLAY_ALBUM;
}

bool CreditManager::startPlaySong()
{
    if(! hasEnoughCreditsToPlaySong())
    {
        return false;
    }
        
    secondCoin = false;
    credits -= CREDIT_TO_PLAY_SONG;
    
    return true;
}

bool CreditManager::startPlayAlbum()
{
    if(! hasEnoughCreditsToPlayAlbum())
    {
        return false;
    }
        
    secondCoin = false;
    credits -= CREDIT_TO_PLAY_ALBUM;
    
    return true;
}

void CreditManager::creditIncrease()
{
    ++credits;
    secondCoin = false;
}

void CreditManager::creditDecrease()
{
    if(credits > 0)
    {
        --credits;
        secondCoin = false;
    }
}
