#ifndef CREDITMANAGER_H_INCLUDED
#define CREDITMANAGER_H_INCLUDED

#include "ICreditManager.h"

namespace jukebox { namespace creditmanager {

class CreditManager : public ICreditManager
{
public:
    CreditManager();
    ~CreditManager() override = default;
    
    int getCredits() const override;
        
    void coinInsert50() override;
    void coinInsert100() override;
    void coinInsert200() override;

    bool hasEnoughCreditsToPlaySong() const override;
    bool hasEnoughCreditsToPlayAlbum() const override;
    bool startPlaySong() override;
    bool startPlayAlbum() override;
        
    void creditIncrease() override;
    void creditDecrease() override;

private:
    void coinInserted();
    
private:
    int credits;
    bool secondCoin;
};

}}

#endif  // CREDITMANAGER_H_INCLUDED
