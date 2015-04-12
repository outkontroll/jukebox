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

class IGui
{
public:
    virtual ~IGui(){}
    
    virtual void initialise(const String& name) = 0;
    virtual void uninitialise() = 0;
};


#endif  // IGUI_H_INCLUDED
