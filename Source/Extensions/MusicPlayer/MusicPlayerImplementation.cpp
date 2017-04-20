#include "MusicPlayerImplementation.h"
#include "Logger.h"

using namespace juce;
using namespace jukebox::audio;

MusicPlayerImplementation::MusicPlayerImplementation()
    : state(TransportState::Stopped)
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);

    setAudioChannels (0, 2);
}

MusicPlayerImplementation::~MusicPlayerImplementation()
{
    shutdownAudio();
}

void MusicPlayerImplementation::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState(TransportState::Playing);
        else
            changeState(TransportState::Stopped);
    }
}

void MusicPlayerImplementation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void MusicPlayerImplementation::releaseResources()
{
    transportSource.releaseResources();
}

void MusicPlayerImplementation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock(bufferToFill);
}

void MusicPlayerImplementation::playSong(const std::string& song)
{
    juce::File file(song);
    if(!file.existsAsFile())
    {
        LOG_ERROR("File " << song << " does not exists! Skip playing");
        return;
    }

    juce::AudioFormatReader* reader = formatManager.createReaderFor(file);
    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(std::make_unique<juce::AudioFormatReaderSource>(reader, true));
        LOG_INFO("Sample rate: " << reader->sampleRate);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource = std::move(newSource);
        changeState(TransportState::Starting);
    }
}

void MusicPlayerImplementation::stopPlaying()
{
    changeState(TransportState::Stopping);
    LOG_INFO("Stoped playing.");
}

void MusicPlayerImplementation::changeState(TransportState newState)
{
    if (state == newState)
        return;

    state = newState;

    switch (state)
    {
        case TransportState::Stopped:
            transportSource.setPosition (0.0);
            break;
        case TransportState::Starting:
            transportSource.start();
            break;
        case TransportState::Playing:
            break;
        case TransportState::Stopping:
            transportSource.stop();
            break;
    }
}
