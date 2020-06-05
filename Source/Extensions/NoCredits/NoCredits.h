#ifndef NOCREDITS_H_INCLUDED
#define NOCREDITS_H_INCLUDED

#include "ICreditManager.h"

namespace jukebox { namespace creditmanager {

class NoCredits : public ICreditManager
{
public:
    ~NoCredits() override = default;
    
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

};

}}

#endif  // CREDITMANAGER_H_INCLUDED
