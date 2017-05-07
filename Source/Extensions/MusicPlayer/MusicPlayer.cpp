#include "MusicPlayer.h"
#include "Logger.h"

using namespace juce;
using namespace jukebox::audio;

MusicPlayer::MusicPlayer()
    : state(TransportState::Stopped)
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);

    setAudioChannels (0, 2);
}

MusicPlayer::~MusicPlayer()
{
    shutdownAudio();
}

void MusicPlayer::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
        {
            changeState(TransportState::Playing);
            LOG_INFO("Playing");
        }
        else
        {
            changeState(TransportState::Stopped);
            LOG_INFO("Stopped");
        }
    }
}

void MusicPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void MusicPlayer::releaseResources()
{
    transportSource.releaseResources();
}

void MusicPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock(bufferToFill);
}

void MusicPlayer::playSong(const std::string& song)
{
    juce::File file(song);
    if(!file.existsAsFile())
    {
        LOG_ERROR("File " << song << " does not exists! Skip playing");
        return;
    }

    juce::AudioFormatReader* reader = formatManager.createReaderFor(file);
    if (reader == nullptr)
    {
        LOG_ERROR("Can not create format reader for song " << song);
        return;
    }

    LOG_INFO("Playing song: " << song);
    std::unique_ptr<juce::AudioFormatReaderSource> newSource(std::make_unique<juce::AudioFormatReaderSource>(reader, true));
    LOG_INFO("Sample rate: " << reader->sampleRate);
    transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
    readerSource = std::move(newSource);
    changeState(TransportState::Starting);
}

bool MusicPlayer::isPlaying() const
{
    return state != TransportState::Stopped;
}

void MusicPlayer::stopPlaying()
{
    changeState(TransportState::Stopping);
    LOG_INFO("Stoped playing.");
}

void MusicPlayer::changeState(TransportState newState)
{
    if (state == newState)
        return;

    state = newState;

    switch (state)
    {
        case TransportState::Stopped:
            finishedPlayingSignal();
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
