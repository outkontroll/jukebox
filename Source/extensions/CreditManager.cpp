/*
  ==============================================================================

    CreditManager.cpp
    Created: 16 Feb 2015 1:21:36pm
    Author:  bakos

  ==============================================================================
*/

#include "CreditManager.h"

CreditManager::CreditManager()
: credit(0), secondCoin(false)
{
    
}

CreditManager::~CreditManager()
{
    
}

unsigned int CreditManager::getCredit() const
{
    return credit;
}

void CreditManager::insert50()
{    
    if(secondCoin)
    {
        secondCoin = false;
        credit += 2;
    }
    else
    {
        secondCoin = true;
        ++credit;
    }
}

void CreditManager::insert100()
{
    insert50();
    insert50();
}

void CreditManager::insert200()
{
    insert100();
    insert100();
}

bool CreditManager::onStartPlaySong()
{
    if(credit == 0)
        return false;
        
    secondCoin = false;
    --credit;
    
    return true;
}

bool CreditManager::onStartPlayAlbum()
{
    if(credit < 6)
        return false;
        
    secondCoin = false;
    credit -= 6;
    
    return true;
}
