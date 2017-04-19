#include "MusicPlayerImplementation.h"
#include "Logger.h"
#include <array>

using namespace juce;
using namespace jukebox::audio;

const std::array<std::string, 3> filesToPlay = { "/home/adam/Music/test_data/wav/AUTORUN.WAV",
                                                 "/home/adam/Music/test_data/Mp3/MAINMENU.MP3",
                                                 "/home/adam/Music/test_data/Mp3/LoopLepr.mp3"};

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

void MusicPlayerImplementation::playSong(Song /*song*/)
{/**/
    //TODO: play a song
    static int fileToPlay = 0;
    fileToPlay = fileToPlay % 3;
    juce::File file (filesToPlay[fileToPlay++]);
    if(!file.existsAsFile())
    {
        LOG_ERROR("Nem letezik ez a szar");
    }

    LOG_INFO("Ezt jatszuk: " << file.getFullPathName().toStdString());

    juce::AudioFormatReader* reader = formatManager.createReaderFor(file);/*/
    FileChooser chooser ("Select a Wave file to play...",
                                 File::nonexistent,
                                 "*.WAV");                                        // [7]

            if (chooser.browseForFileToOpen())                                    // [8]
            {
                File file (chooser.getResult());                                  // [9]
                AudioFormatReader* reader = formatManager.createReaderFor (file); // [10]/*/
    if (reader != nullptr)
    {
        /**/
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(std::make_unique<juce::AudioFormatReaderSource>(reader, true));
        LOG_INFO("Sample rate: " << reader->sampleRate);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        //playButton.setEnabled(true);
        readerSource = std::move(newSource);/*/

        ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource (reader, true); // [11]
        transportSource.setSource (newSource, 0, nullptr, reader->sampleRate);                         // [12]
        //playButton.setEnabled (true);                                                                  // [13]
        readerSource = newSource.release();                                                            // [14]

        LOG_INFO("Kiskakas");//*/
        changeState(TransportState::Starting);
    }
           // }
}

void MusicPlayerImplementation::playAlbum(Album /*album*/)
{
    //TODO: play an album
}

void MusicPlayerImplementation::stopPlaying()
{
    //TODO: stop playing
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
            //stopButton.setEnabled (false);
            //playButton.setEnabled (true);
            transportSource.setPosition (0.0);
            break;
        case TransportState::Starting:
            //playButton.setEnabled (false);
            transportSource.start();
            break;
        case TransportState::Playing:
            //stopButton.setEnabled (true);
            break;
        case TransportState::Stopping:
            transportSource.stop();
            break;
    }
}
