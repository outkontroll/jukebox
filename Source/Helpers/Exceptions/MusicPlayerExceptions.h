#ifndef MUSICPLAYEREXCEPTIONS_H
#define MUSICPLAYEREXCEPTIONS_H

#include "JukeboxException.h"

namespace jukebox { namespace audio {

struct MusicPlayerException : public jukebox::JukeboxException {};

struct FileNotFoundException : public MusicPlayerException {};

struct FormatReaderException : public MusicPlayerException {};

}}

#endif //MUSICPLAYEREXCEPTIONS_H
