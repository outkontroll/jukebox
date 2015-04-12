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

class ICore;

class jukeboxApplication : public JUCEApplication
{
public:
    jukeboxApplication();
    ~jukeboxApplication();
    
    const String getApplicationName() override;
    
    const String getApplicationVersion() override;
    
    bool moreThanOneInstanceAllowed() override;
    
    void initialise (const String& commandLine) override;
    
    void shutdown() override;
    
    void systemRequestedQuit() override;
    
    void anotherInstanceStarted(const String& commandLine) override;
    
private:
    std::unique_ptr<ICore> core;
};


#endif  // APPLICATION_H_INCLUDED
