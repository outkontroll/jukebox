#include "gtest/gtest.h"
#include "MainComponentMock.h"
#include "GuiTester.h"

using namespace jukebox::gui;

class GuiTest : public ::testing::Test
{    
protected:
    GuiTest()
        : Test(),
          gui(std::make_unique<MainComponentMock>()),
          mainComponentMock(gui.getMainComponentMock())
    {
    }

    GuiTester gui;
    MainComponentMock* mainComponentMock;
};

TEST_F(GuiTest, empty)
{
    int i = 2;
    EXPECT_EQ(0, i % 2);
}
