#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED


#include "JuceHeader.h"
#include "Signals.hpp"
#include <memory>

namespace jukebox
{
    namespace core
    {
        class Core;
    }
}

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
    void exitRequested();

private:
    jukebox::signals::Slot eventsSlot;

    std::unique_ptr<jukebox::core::Core> core;
};


#endif  // APPLICATION_H_INCLUDED
