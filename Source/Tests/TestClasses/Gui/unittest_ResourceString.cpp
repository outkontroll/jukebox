#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ResourceId.h"
#include "ResourceString.h"

using namespace testing;
using namespace jukebox;
using namespace jukebox::gui;

namespace {
    const char* UnknownError = "Unknown error";
    const char* ErrorFewCreditsSong = "Too few credits to play a song!";
    const char* ErrorFewCreditsAlbum = "Too few credits to play an album!";
    const char* ErrorDuringSongPlaying = "An unexpected error occured during playing song: ";
    const char* ErrorDuringAlbumPlaying = "An unexpected error occured during playing album: ";
    const char* ErrorSongNotExists = "The given song is not existing!";
    const char* ErrorAlbumNotExists = "The given album is not existing!";
    const char* ErrorAlbumEmpty = "The given album does not contain any song!";
    const char* WarningNotPlayingSong = "Music already stopped!";
    const char* ErrorImageNotFound = "Image not available";
    const char* ErrorNegativeNumber = "Negative values are not accepted!";
    const char* ErrorWrongNumber = "Wrong number!";
    const char* ErrorWrongPassword = "Wrong password!";
    const char* ErrorDuringAlbumImport = "Could not import the directory!";
    const char* Playing = "Playing";
    const char* DefaultArtistName = "Selection Album";
}

TEST(ResourceStringTest, strings)
{
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorDuringAlbumPlaying), StrEq(ErrorDuringAlbumPlaying));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorFewCreditsAlbum), StrEq(ErrorFewCreditsAlbum));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorDuringSongPlaying), StrEq(ErrorDuringSongPlaying));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorFewCreditsSong), StrEq(ErrorFewCreditsSong));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorSongNotExists), StrEq(ErrorSongNotExists));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorAlbumNotExists), StrEq(ErrorAlbumNotExists));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorAlbumEmpty), StrEq(ErrorAlbumEmpty));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::WarningNotPlayingSong), StrEq(WarningNotPlayingSong));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorImageNotFound), StrEq(ErrorImageNotFound));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorNegativeNumber), StrEq(ErrorNegativeNumber));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorWrongNumber), StrEq(ErrorWrongNumber));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorWrongPassword), StrEq(ErrorWrongPassword));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::ErrorDuringAlbumImport), StrEq(ErrorDuringAlbumImport));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::Playing), StrEq(Playing));
    ASSERT_THAT(Resources::getResourceStringFromId(ResourceId::DefaultArtistName), StrEq(DefaultArtistName));
    ASSERT_THAT(Resources::getResourceStringFromId(static_cast<ResourceId>(20)), StrEq(UnknownError));
}
