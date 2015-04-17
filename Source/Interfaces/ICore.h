/*
  ==============================================================================

    ICore.h
    Created: 14 Mar 2015 3:27:52am
    Author:  adam

  ==============================================================================
*/

#ifndef ICORE_H_INCLUDED
#define ICORE_H_INCLUDED

#include <string>

namespace jukebox { namespace core {

class ICore
{
public:
    virtual ~ICore(){}
    
    virtual void initialise(const std::string& name) = 0;
    virtual void uninitialise() = 0;
};

}}

#endif  // ICORE_H_INCLUDED
