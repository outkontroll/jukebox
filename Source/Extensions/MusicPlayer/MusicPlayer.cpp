#include "MusicPlayer.h"
#include "Formaters.h"
#include "Logger.h"
#include "JuceHeader.h"
#include <array>

using namespace jukebox;
using namespace jukebox::audio;

const std::array<std::string, 3> filesToPlay = { "/home/adam/Music/test_data/Mp3/MAINMENU.MP3",
                                                 "/home/adam/Music/test_data/Mp3/LoopLepr.mp3",
                                                 "/home/adam/Music/test_data/wav/AUTORUN.WAV" };

enum class TransportState
{
    Stopped,
    Starting,
    Playing,
    Stopping
};

class MusicPlayerImplementation : public juce::ChangeListener, public IMusicPlayer
{
public:
    MusicPlayerImplementation();
    
    void changeListenerCallback(juce::ChangeBroadcaster* /*source*/) override;

    void playSong(Song) override;
    void playAlbum(Album) override;
    
    void stopPlaying() override;
    
private:
    TransportState state;
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
};













MusicPlayer::MusicPlayer() :
    pImpl(std::make_unique<MusicPlayerImplementation>())
{
}

void MusicPlayer::playSong(Song song)
{
    LOG_INFO("Playing: " << FillWithLeadingZeros(song.getAlbumNumber(), 3) << " " << FillWithLeadingZeros(song.getSongNumber(), 2));
    pImpl->playSong(song);
}

void MusicPlayer::playAlbum(Album album)
{
    LOG_INFO("Playing: " << FillWithLeadingZeros(album.getAlbumNumber(), 3));
    pImpl->playAlbum(album);
}

void MusicPlayer::stopPlaying()
{
    LOG_INFO("Stoped playing.");
    pImpl->stopPlaying();
}








MusicPlayerImplementation::MusicPlayerImplementation()
    : state(TransportState::Stopped)
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);
}

void MusicPlayerImplementation::changeListenerCallback(juce::ChangeBroadcaster* /*source*/)
{
    //TODO do something
}

void MusicPlayerImplementation::playSong(Song song)
{
    //TODO: play a song
    LOG_INFO("Playing: " << FillWithLeadingZeros(song.getAlbumNumber(), 3) << " " << FillWithLeadingZeros(song.getSongNumber(), 2));
}

void MusicPlayerImplementation::playAlbum(Album album)
{
    //TODO: play an album
    LOG_INFO("Playing: " << FillWithLeadingZeros(album.getAlbumNumber(), 3));
}

void MusicPlayerImplementation::stopPlaying()
{
    //TODO: stop playing
    LOG_INFO("Stoped playing.");
}
