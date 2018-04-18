#ifndef JUCEEVENTLOOPRUNNER_H
#define JUCEEVENTLOOPRUNNER_H

#include "JuceHeader.h"

class JuceEventLoopRunner
{
public:
    ~JuceEventLoopRunner();
    void runEventLoop(int millisecs);

private:
    juce::MessageManager* messageManager = juce::MessageManager::getInstance();
};

JuceEventLoopRunner::~JuceEventLoopRunner()
{
    juce::MessageManager::deleteInstance();
}

void JuceEventLoopRunner::runEventLoop(int millisecs)
{
    messageManager->runDispatchLoopUntil(millisecs + 20);
}

#endif // JUCEEVENTLOOPRUNNER_H
