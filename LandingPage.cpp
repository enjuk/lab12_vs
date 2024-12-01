#include "LandingPage.h"
#include "TUI.hpp"
#include <iostream>


LandingPage::LandingPage() : LandingPage(nullptr)
{
}

LandingPage::LandingPage(const std::string& userInfo)
{
}

LandingPage::LandingPage(Student* userPtr)
{
   this->userPtr = userPtr;
}

void LandingPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayOptions();

   std::cout << promptOffset;
   savePromptLocation();
}

