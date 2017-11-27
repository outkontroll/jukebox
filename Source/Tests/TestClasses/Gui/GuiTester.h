#ifndef GUITESTER_H
#define GUITESTER_H

#include "Gui.h"
#include "MainComponentMock.h"
#include "FileSystemMock.h"
#include "gmock/gmock.h"

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

#endif // GUITESTER_H
