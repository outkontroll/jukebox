# music jukebox
A small project to emulate a jukebox. It plays digital audio files (mp3, wav,...) organized in numbered directories.

*Supported compilers:*
* gcc 7
* clang 6

It is not tested with MSVC, probably only a small tweaking is needed (other macros in the JUCE's AppConfig.h file) 

*C++17 standard is used*

CMake 3.10 required

With gcc and lcov it is possible to get code coverage for the tests, use <code>TEST_COVERAGE=ON</code> cmake option in debug mode and after
compilation use <code>make code_coverage</code>

The used 3rd-parties are in the Libraries folder (what a surprise), compiled separately from the main project (also CMake).

## Usage
A music file is identified by an album ID (001-999) and a song ID (01-99)

*Keyboard input*
- h: list songs in the selected album
- c: jump selection
- .: play selected song
- o, p, l: simulate insertion of different coins
- backspace: remove currently played song
- esc: accesss setup page
- F4: exit program
- 0-9: manually input the song-to-play ID 

*to be continued...*
