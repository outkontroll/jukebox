/*
  ==============================================================================

    Application.h
    Created: 14 Mar 2015 3:34:51am
    Author:  adam

  ==============================================================================
*/

#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED


#include "JuceHeader.h"
#include <memory>

namespace jukebox { namespace core {
    class ICore;
}}

class jukeboxApplication : public juce::JUCEApplication
{
public:
    jukeboxApplication();
    ~jukeboxApplication();
    
    const juce::String getApplicationName() override;
    
    const juce::String getApplicationVersion() override;
    
    bool moreThanOneInstanceAllowed() override;
    
    void initialise (const juce::String& commandLine) override;
    
    void shutdown() override;
    
    void systemRequestedQuit() override;
    
    void anotherInstanceStarted(const juce::String& commandLine) override;
    
private:
    std::unique_ptr<jukebox::core::ICore> core;
};


#endif  // APPLICATION_H_INCLUDED
