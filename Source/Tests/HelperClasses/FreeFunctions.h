#ifndef FREEFUNCTIONS_H
#define FREEFUNCTIONS_H

#include <vector>
#include "gmock/gmock.h"

namespace jukebox {
    class Password;

    namespace audio {
        struct Song;
        struct Album;
    }
}

struct IFoo
{
    virtual ~IFoo() = default;
    virtual void foo() = 0;
    virtual void fooSong(const jukebox::audio::Song&) = 0;
    virtual void fooAlbum(const jukebox::audio::Album&, const std::vector<jukebox::audio::Song>&) = 0;
    virtual void fooString(const std::string&) = 0;
    virtual void fooInt(int) = 0;
    virtual void fooPassword(const jukebox::Password&) = 0;
};

struct FooMock : public IFoo
{
    MOCK_METHOD0(foo, void());
    MOCK_METHOD1(fooSong, void(const jukebox::audio::Song&));
    MOCK_METHOD2(fooAlbum, void(const jukebox::audio::Album&, const std::vector<jukebox::audio::Song>&));
    MOCK_METHOD1(fooString, void(const std::string&));
    MOCK_METHOD1(fooInt, void(int));
    MOCK_METHOD1(fooPassword, void(const jukebox::Password&));
};

#endif // FREEFUNCTIONS_H
