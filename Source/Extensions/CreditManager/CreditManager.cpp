#include "CreditManager.h"
#include "Logger.h"

using namespace jukebox::creditmanager;

namespace {
    const int creditToPlaySong = 1;
    const int creditToPlayAlbum = 18;
}

CreditManager::CreditManager()
:   credits(0), 
    secondCoin(false)
{
}

int CreditManager::getCredits() const
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

bool CreditManager::hasEnoughCreditsToPlaySong() const
{
    return credits >= creditToPlaySong;
}

bool CreditManager::hasEnoughCreditsToPlayAlbum() const
{
    return credits >= creditToPlayAlbum;
}

bool CreditManager::startPlaySong()
{
    if(!hasEnoughCreditsToPlaySong())
    {
        LOG_ERROR("there is not enough credit: " << credits);
        return false;
    }
        
    secondCoin = false;
    credits -= creditToPlaySong;
    
    return true;
}

bool CreditManager::startPlayAlbum()
{
    if(!hasEnoughCreditsToPlayAlbum())
    {
        LOG_ERROR("there is not enough credit: " << credits);
        return false;
    }
        
    secondCoin = false;
    credits -= creditToPlayAlbum;
    
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
    
