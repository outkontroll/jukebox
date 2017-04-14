#include "MusicPlayer.h"
#include <iostream>
#include "Formaters.h"
#include "Logger.h"
#include "JuceHeader.h"

using namespace jukebox;
using namespace jukebox::audio;

class MusicPlayerImplementation : public IMusicPlayer
{
public:
    MusicPlayerImplementation();
    
    void playSong(Song) override;
    void playAlbum(Album) override;
    
    void stopPlaying() override;
    
private:
    juce::AudioFormatManager formatManager;
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
{
    formatManager.registerBasicFormats();
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
