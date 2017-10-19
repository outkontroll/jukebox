#ifndef CREDITMANAGERMOCK_H
#define CREDITMANAGERMOCK_H

#include "ICreditManager.h"
#include "gmock/gmock.h"

struct CreditManagerMock : public jukebox::creditmanager::ICreditManager
{
    // ICreditManager interface
public:
    MOCK_CONST_METHOD0(getCredits, unsigned int ());
    MOCK_METHOD0(coinInsert50, void());
    MOCK_METHOD0(coinInsert100, void());
    MOCK_METHOD0(coinInsert200, void());
    MOCK_CONST_METHOD0(hasEnoughCreditsToPlaySong, bool());
    MOCK_CONST_METHOD0(hasEnoughCreditsToPlayAlbum, bool());
    MOCK_METHOD0(startPlaySong, bool());
    MOCK_METHOD0(startPlayAlbum, bool());
    MOCK_METHOD0(creditIncrease, void());
    MOCK_METHOD0(creditDecrease, void());
};

#endif // CREDITMANAGERMOCK_H
