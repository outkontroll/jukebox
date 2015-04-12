/*
  ==============================================================================

    IGui.h
    Created: 14 Mar 2015 3:28:06am
    Author:  adam

  ==============================================================================
*/

#ifndef IGUI_H_INCLUDED
#define IGUI_H_INCLUDED

#include "JuceHeader.h"
#include "Signals.hpp"

namespace jukebox { namespace gui {
    
class IGui
{
public:
    virtual ~IGui(){}
    
    virtual void initialise(const String& name) = 0;
    virtual void uninitialise() = 0;
    
    virtual void refreshCredits(unsigned int credits) = 0;
    virtual void showStatusMessage(const String& message) = 0;

public:
    jukebox::signals::Signal<> coinInserted50Signal;
    jukebox::signals::Signal<> coinInserted100Signal;
    jukebox::signals::Signal<> coinInserted200Signal;
    
    jukebox::signals::Signal<> playingSongSignal;
    jukebox::signals::Signal<> playingAlbumSignal;
    
    jukebox::signals::Signal<> creditIncreaseSignal;
    jukebox::signals::Signal<> creditDecreaseSignal;
    
    jukebox::signals::Signal<> exitRequestedSignal;
};

}}

#endif  // IGUI_H_INCLUDED
