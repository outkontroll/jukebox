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
#include "Signals.hpp"
#include <memory>

namespace jukebox 
{
    namespace core
    {
        class ICore;
    }
    namespace gui
    {
        class IGui;
    }
    namespace creditmanager
    {
        class ICreditManager;
    }
    namespace audio
    {
        class IMusicPlayer;
    }
    namespace statistics
    {
        class IStatistics;
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

    std::shared_ptr<jukebox::core::ICore> core;
    std::shared_ptr<jukebox::gui::IGui> gui;
    std::shared_ptr<jukebox::creditmanager::ICreditManager> creditManager;
    std::shared_ptr<jukebox::audio::IMusicPlayer> musicPlayer;
    std::shared_ptr<jukebox::statistics::IStatistics> statistics;
};


#endif  // APPLICATION_H_INCLUDED
