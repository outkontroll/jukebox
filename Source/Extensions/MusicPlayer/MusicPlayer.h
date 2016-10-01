/*
  ==============================================================================

    MusicPlayer.h
    Created: 12 Apr 2015 3:17:00pm
    Author:  bakos

  ==============================================================================
*/

#ifndef MUSICPLAYER_H_INCLUDED
#define MUSICPLAYER_H_INCLUDED

#include "IMusicPlayer.h"
#include "JuceHeader.h"

namespace jukebox { namespace audio {
  
class MusicPlayer : public IMusicPlayer
{
public:
    MusicPlayer();

    void playSong(Song) override;
    void playAlbum(Song) override;
    
    void stopPlaying() override;
    
private:
    juce::AudioFormatManager formatManager;
};

}}
    
#endif  // MUSICPLAYER_H_INCLUDED
