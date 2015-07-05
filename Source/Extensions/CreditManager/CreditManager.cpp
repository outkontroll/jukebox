/*
  ==============================================================================

    KreditManager.cpp
    Created: 16 Feb 2015 1:21:36pm
    Author:  bakos

  ==============================================================================
*/

#include "CreditManager.h"
#include "Logger.h"

using namespace jukebox::creditmanager;

const unsigned int CREDIT_TO_PLAY_SONG = 1;
const unsigned int CREDIT_TO_PLAY_ALBUM = 6;

CreditManager::CreditManager()
: credits(0), 
    secondCoin(false)
{
    
}

unsigned int CreditManager::getCredits() const
{
    return credits;
}

void CreditManager::coinInsert50()
{    
    coinInserted();
    
    LOG_INFO("a 50 coin inserted");
}

void CreditManager::coinInsert100()
{
    coinInserted();
    coinInserted();
    
    LOG_INFO("a 100 coin inserted");
}

void CreditManager::coinInsert200()
{
    coinInserted();
    coinInserted();
    coinInserted();
    coinInserted();
    
    LOG_INFO("a 200 coin inserted");
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
        LOG_ERROR("there is not enough credit: " << credits);
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
        LOG_ERROR("there is not enough credit: " << credits);
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
    
    LOG_INFO("free credit");
}

void CreditManager::creditDecrease()
{
    if(credits > 0)
    {
        --credits;
        secondCoin = false;
    }
    
    LOG_INFO("take credit");
}

void CreditManager::coinInserted()
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
    
