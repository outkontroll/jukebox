#include "gtest/gtest.h"
#include "MainComponentMock.h"
#include "GuiTester.h"
#include "Song.h"
#include "FreeFunctions.h"

using namespace jukebox::gui;
using namespace jukebox::audio;
using namespace testing;

class GuiTest : public ::testing::Test
{    
protected:
    void SetUp() override
    {
        auto mainCompMock = std::make_unique<MainComponentMock>();
        mainComponentMock = mainCompMock.get();
        gui = std::make_unique<GuiTester>(std::move(mainCompMock));
    }

    std::unique_ptr<GuiTester> gui;
    MainComponentMock* mainComponentMock;

    jukebox::signals::Slot eventsSlot;
};

TEST_F(GuiTest, WhenMainComponentSendsPlayNextSongSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooSong, gui->playNextSongSignal);

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(fooMock, fooSong(song));

    mainComponentMock->playNextSongSignal(song);
}
