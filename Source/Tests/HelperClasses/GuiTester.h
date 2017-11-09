#ifndef GUITESTER_H
#define GUITESTER_H

#include "Gui.h"
#include "MainComponentMock.h"
#include "gmock/gmock.h"

struct GuiTester : public jukebox::gui::Gui
{
    GuiTester(std::unique_ptr<MainComponentMock> mainComponent_)
        : Gui(std::move(mainComponent_))
    {
    }

    MainComponentMock* getMainComponentMock()
    {
        //TODO
        return nullptr;
    }
};

#endif // GUITESTER_H
