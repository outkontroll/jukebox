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


class CreditManager : public ICreditManager
{
    public:
        CreditManager();
        ~CreditManager();
    
        unsigned int getCredit() const override;
        
        void insert50() override;
        void insert100() override;
        void insert200() override;
        
        bool onStartPlaySong() override;
        bool onStartPlayAlbum() override;
        
    private:
        unsigned int credit;
        bool secondCoin;
};


#endif  // CREDITMANAGER_H_INCLUDED
