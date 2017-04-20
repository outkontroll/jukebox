#ifndef MUSICPLAYERIMPLEMENTATION_H
#define MUSICPLAYERIMPLEMENTATION_H

#include <memory>
#include "IMusicPlayer.h"
#include "JuceHeader.h"

namespace jukebox { namespace audio {

enum class TransportState
{
    Stopped,
    Starting,
    Playing,
    Stopping
};

class MusicPlayerImplementation : public juce::ChangeListener,
                                  public juce::AudioAppComponent,
                                  public IMusicPlayer
{
public:
    MusicPlayerImplementation();
    ~MusicPlayerImplementation();

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    void playSong(const std::string&) override;
    void stopPlaying() override;

private:
    void changeState(TransportState newState);

    TransportState state;
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
};

}}

#endif //MUSICPLAYERIMPLEMENTATION_H
