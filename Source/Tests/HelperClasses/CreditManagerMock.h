#ifndef CREDITMANAGERMOCK_H
#define CREDITMANAGERMOCK_H

#include "ICreditManager.h"

struct CreditManagerMock : public jukebox::creditmanager::ICreditManager
{
    // ICreditManager interface
public:
    unsigned int getCredits() const override
    {
        return 0;
    }
    void coinInsert50() override
    {
    }
    void coinInsert100() override
    {
    }
    void coinInsert200() override
    {
    }
    bool hasEnoughCreditsToPlaySong() const override
    {
        return false;
    }
    bool hasEnoughCreditsToPlayAlbum() const override
    {
        return false;
    }
    bool startPlaySong() override
    {
        return false;
    }
    bool startPlayAlbum() override
    {
        return false;
    }
    void creditIncrease() override
    {
    }
    void creditDecrease() override
    {
    }
};

#endif // CREDITMANAGERMOCK_H
