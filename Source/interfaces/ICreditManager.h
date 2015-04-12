/*
  ==============================================================================

    ICreditManager.h
    Created: 9 Mar 2015 7:43:58pm
    Author:  bakos

  ==============================================================================
*/

#ifndef ICREDITMANAGER_H_INCLUDED
#define ICREDITMANAGER_H_INCLUDED


class ICreditManager
{
    public:
        virtual ~ICreditManager(){}
    
        virtual unsigned int getCredit() const = 0;
        
        virtual void insert50() = 0;
        virtual void insert100() = 0;
        virtual void insert200() = 0;
        
        virtual bool onStartPlaySong() = 0;
        virtual bool onStartPlayAlbum() = 0;
};


#endif  // ICREDITMANAGER_H_INCLUDED
