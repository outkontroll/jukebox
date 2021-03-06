#ifndef GUITESTER_H
#define GUITESTER_H

#include "gtest/gtest.h"
#include "Gui.h"
#include "MainComponentMock.h"
#include "FileSystemMock.h"
#include "Song.h"

struct GuiTester : public jukebox::gui::Gui
{
    GuiTester(std::unique_ptr<MainComponentMock> mainComponent_,
              std::unique_ptr<FileSystemMock> fileSystemMock_)
        : Gui(std::move(mainComponent_)),
          fileSystemMock(std::move(fileSystemMock_))
    {
    }

    std::unique_ptr<FileSystemMock> fileSystemMock;
};

class GuiTest : public testing::Test
{
protected:
    void SetUp() override
    {
        auto mainCompMock = std::make_unique<testing::StrictMock<MainComponentMock>>();
        mainComponentMock = mainCompMock.get();
        auto filesysMock = std::make_unique<testing::NiceMock<FileSystemMock>>();
        fileSystemMock = filesysMock.get();
        gui = std::make_unique<GuiTester>(std::move(mainCompMock), std::move(filesysMock));
        std::vector<jukebox::audio::AlbumInfo> vec{};
        ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(vec));
        EXPECT_CALL(*mainComponentMock, setAlbumsForMusicSetup(vec));
        gui->setFileSystem(fileSystemMock);
    }

    std::unique_ptr<GuiTester> gui;
    testing::StrictMock<MainComponentMock>* mainComponentMock;
    testing::NiceMock<FileSystemMock>* fileSystemMock;

    jukebox::signals::Slot eventsSlot;
};

#endif // GUITESTER_H
