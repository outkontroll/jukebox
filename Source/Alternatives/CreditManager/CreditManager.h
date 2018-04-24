#ifndef CREDITMANAGER_H_INCLUDED
#define CREDITMANAGER_H_INCLUDED

#include <boost/config.hpp>
#include "ICreditManager.h"

namespace jukebox { namespace alternatives { namespace creditmanager {

class CreditManagerFree : public jukebox::creditmanager::ICreditManager
{
public:
    ~CreditManagerFree() override = default;
    
    unsigned int getCredits() const override;

    void coinInsert50() override;
    void coinInsert100() override;
    void coinInsert200() override;

    bool hasEnoughCreditsToPlaySong() const override;
    bool hasEnoughCreditsToPlayAlbum() const override;
    bool startPlaySong() override;
    bool startPlayAlbum() override;
        
    void creditIncrease() override;
    void creditDecrease() override;
};

extern "C" BOOST_SYMBOL_EXPORT CreditManagerFree plugin;
CreditManagerFree plugin;

}}}

#endif  // CREDITMANAGER_H_INCLUDED
