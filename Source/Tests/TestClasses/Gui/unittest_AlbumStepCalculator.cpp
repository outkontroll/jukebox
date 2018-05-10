#include "gtest/gtest.h"
#include "AlbumStepCalculator.h"

using namespace jukebox::gui;
using namespace testing;
using namespace std;

// getNextSelectedAlbumIndex

TEST(AlbumStepCalculator, GivenAlbumSizeIsDivisibleWithStep_getNextSelectedAlbumIndex_increase)
{
    AlbumStepCalculator calc{24, 8};

    ASSERT_EQ(2, calc.getNextSelectedAlbumId(1, true));
    ASSERT_EQ(9, calc.getNextSelectedAlbumId(8, true));
    ASSERT_EQ(1, calc.getNextSelectedAlbumId(24, true));
}

TEST(AlbumStepCalculator, GivenAlbumSizeIsDivisibleWithStep_getNextSelectedAlbumIndex_decrease)
{
    AlbumStepCalculator calc{24, 8};

    ASSERT_EQ(1, calc.getNextSelectedAlbumId(2, false));
    ASSERT_EQ(8, calc.getNextSelectedAlbumId(9, false));
    ASSERT_EQ(24, calc.getNextSelectedAlbumId(1, false));
}

TEST(AlbumStepCalculator, GivenAlbumSizeIsNotDivisibleWithStep_getNextSelectedAlbumIndex_increase)
{
    AlbumStepCalculator calc{25, 8};

    ASSERT_EQ(2, calc.getNextSelectedAlbumId(1, true));
    ASSERT_EQ(9, calc.getNextSelectedAlbumId(8, true));
    ASSERT_EQ(1, calc.getNextSelectedAlbumId(25, true));
    ASSERT_EQ(25, calc.getNextSelectedAlbumId(24, true));
}

TEST(AlbumStepCalculator, GivenAlbumSizeIsNotDivisibleWithStep_getNextSelectedAlbumIndex_decrease)
{
    AlbumStepCalculator calc{25, 8};

    ASSERT_EQ(1, calc.getNextSelectedAlbumId(2, false));
    ASSERT_EQ(8, calc.getNextSelectedAlbumId(9, false));
    ASSERT_EQ(25, calc.getNextSelectedAlbumId(1, false));
    ASSERT_EQ(23, calc.getNextSelectedAlbumId(24, false));
}

// getNextVisibleAlbumsIndex

TEST(AlbumStepCalculator, GivenAlbumSizeIsDivisibleWithStep_getNextVisibleAlbumsIndex_increase)
{
    AlbumStepCalculator calc{24, 8};

    ASSERT_EQ(9, calc.getNextVisibleAlbumsId(1, true));
    ASSERT_EQ(17, calc.getNextVisibleAlbumsId(9, true));
    ASSERT_EQ(1, calc.getNextVisibleAlbumsId(17, true));
}

TEST(AlbumStepCalculator, GivenAlbumSizeIsDivisibleWithStep_getNextVisibleAlbumIndex_decrease)
{
    AlbumStepCalculator calc{24, 8};

    ASSERT_EQ(1, calc.getNextVisibleAlbumsId(9, false));
    ASSERT_EQ(9, calc.getNextVisibleAlbumsId(17, false));
    ASSERT_EQ(17, calc.getNextVisibleAlbumsId(1, false));
}

TEST(AlbumStepCalculator, GivenAlbumSizeIsNotDivisibleWithStep_getNextVisibleAlbumsIndex_increase)
{
    AlbumStepCalculator calc{26, 8};

    ASSERT_EQ(9, calc.getNextVisibleAlbumsId(1, true));
    ASSERT_EQ(17, calc.getNextVisibleAlbumsId(9, true));
    ASSERT_EQ(1, calc.getNextVisibleAlbumsId(25, true));
}

TEST(AlbumStepCalculator, GivenAlbumSizeIsNotDivisibleWithStep_getNextVisibleAlbumIndex_decrease)
{
    AlbumStepCalculator calc{26, 8};

    ASSERT_EQ(1, calc.getNextVisibleAlbumsId(9, false));
    ASSERT_EQ(9, calc.getNextVisibleAlbumsId(17, false));
    ASSERT_EQ(25, calc.getNextVisibleAlbumsId(1, false));
}

// getNextSelectedAlbumIndexOnSamePage

TEST(AlbumStepCalculator, GivenFullPage_getNextSelectedAlbumIndexOnSamePage)
{
    AlbumStepCalculator calc{24, 8};

    ASSERT_EQ(10, calc.getNextSelectedAlbumIdOnSamePage(9, 9));
    ASSERT_EQ(9, calc.getNextSelectedAlbumIdOnSamePage(9, 16));
}

TEST(AlbumStepCalculator, GivenAlmostEmptyPageLastIndex_getNextSelectedAlbumIndexOnSamePage)
{
    AlbumStepCalculator calc{9, 8};

    ASSERT_EQ(9, calc.getNextSelectedAlbumIdOnSamePage(9, 9));
}

TEST(AlbumStepCalculator, GivenNotFullPage_getNextSelectedAlbumIndexOnSamePage)
{
    AlbumStepCalculator calc{10, 8};

    ASSERT_EQ(9, calc.getNextSelectedAlbumIdOnSamePage(9, 10));
}

TEST(AlbumStepCalculator, GivenEmptyPage_getNextSelectedAlbumIndexOnSamePage)
{
    AlbumStepCalculator calc{0, 8};

    ASSERT_EQ(0, calc.getNextSelectedAlbumIdOnSamePage(0, 0));
}

// shouldStepVisibleAlbums

TEST(SongStepCalculator, simpleSelectionStep)
{
    AlbumStepCalculator calc{10, 8};

    ASSERT_FALSE(calc.shouldStepVisibleAlbums(1, 2, true));
    ASSERT_FALSE(calc.shouldStepVisibleAlbums(1, 1, false));
    ASSERT_FALSE(calc.shouldStepVisibleAlbums(9, 10, true));
}

TEST(SongStepCalculator, pageTurnSelectionStep)
{
    AlbumStepCalculator calc{10, 8};

    ASSERT_TRUE(calc.shouldStepVisibleAlbums(1, 9, true));
    ASSERT_TRUE(calc.shouldStepVisibleAlbums(9, 1, false));
}

TEST(SongStepCalculator, overflowSelectionStep)
{
    AlbumStepCalculator calc{25, 8};

    ASSERT_TRUE(calc.shouldStepVisibleAlbums(25, 1, true));
}

TEST(SongStepCalculator, underflowSelectionStep)
{
    AlbumStepCalculator calc{25, 8};

    ASSERT_TRUE(calc.shouldStepVisibleAlbums(1, 25, false));
}

// SongStepCalculator
// getNextSelectedSongIndex

TEST(SongStepCalculator, GivenMultipleSongs_getNextSelectedSongIndex)
{
    SongStepCalculator calc;

    ASSERT_EQ(2, calc.getNextSelectedSongIndex(10, 1));
    ASSERT_EQ(0, calc.getNextSelectedSongIndex(10, 10));
}

TEST(SongStepCalculator, GivenEmptySongs_getNextSelectedSongIndex)
{
    SongStepCalculator calc;

    ASSERT_EQ(0, calc.getNextSelectedSongIndex(0, 0));
}
