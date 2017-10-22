#ifndef MUSICPLAYER_H_INCLUDED
#define MUSICPLAYER_H_INCLUDED

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

class MusicPlayer : public juce::ChangeListener,
                    public juce::AudioAppComponent,
                    public IMusicPlayer
{
public:
    MusicPlayer();
    ~MusicPlayer();

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    void playSong(const std::string&) override;
    bool isPlaying() const noexcept override;
    void stopPlaying() override;

private:
    void changeState(TransportState newState);

    TransportState state;
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
};

}}

#endif  // MUSICPLAYER_H_INCLUDED
