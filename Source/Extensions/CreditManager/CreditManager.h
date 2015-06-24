/*
  ==============================================================================

    CreditManager.h
    Created: 16 Feb 2015 1:21:36pm
    Author:  bakos

  ==============================================================================
*/

#ifndef CREDITMANAGER_H_INCLUDED
#define CREDITMANAGER_H_INCLUDED

#include "ICreditManager.h"

namespace jukebox { namespace creditmanager {

class CreditManager : public ICreditManager
{
public:
    CreditManager();
    
    unsigned int getCredits() const override;
        
    void coinInsert50() override;
    void coinInsert100() override;
    void coinInsert200() override;

    bool hasEnoughCreditsToPlaySong() override;
    bool hasEnoughCreditsToPlayAlbum() override;
    bool startPlaySong() override;
    bool startPlayAlbum() override;
        
    void creditIncrease() override;
    void creditDecrease() override;

private:
    void coinInserted();
    
private:
    unsigned int credits;
    bool secondCoin;
};

}}

#endif  // CREDITMANAGER_H_INCLUDED
