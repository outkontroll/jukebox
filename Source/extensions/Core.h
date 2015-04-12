/*
  ==============================================================================

    Core.h
    Created: 14 Mar 2015 3:30:39am
    Author:  adam

  ==============================================================================
*/

#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include "ICore.h"
#include <memory>

class IGui;

class Core : public ICore
{
public:
    Core();
    ~Core();
    
    void initialise(const String& name) override;
    void uninitialise() override;
    
private:
    std::unique_ptr<IGui> gui;
};

#endif  // CORE_H_INCLUDED
