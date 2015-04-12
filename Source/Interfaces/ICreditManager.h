/*
  ==============================================================================

    KreditManager.h
    Created: 16 Feb 2015 1:21:36pm
    Author:  bakos

  ==============================================================================
*/

#ifndef ICREDITMANAGER_H_INCLUDED
#define ICREDITMANAGER_H_INCLUDED

namespace jukebox { namespace creditmanager {

class ICreditManager
{
public:
    virtual ~ICreditManager(){}
    
    virtual unsigned int getCredits() const = 0;
        
    virtual void coinInsert50() = 0;
    virtual void coinInsert100() = 0;
    virtual void coinInsert200() = 0;

    virtual bool hasEnoughCreditsToPlaySong() = 0;
    virtual bool hasEnoughCreditsToPlayAlbum() = 0;
    virtual bool startPlaySong() = 0;
    virtual bool startPlayAlbum() = 0;
    
    virtual void creditIncrease() = 0;
    virtual void creditDecrease() = 0;
};

}}

#endif  // ICREDITMANAGER_H_INCLUDED
