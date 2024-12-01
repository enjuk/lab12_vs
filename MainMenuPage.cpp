#include "MainMenuPage.h"
#include "TUI.hpp"
#include <iostream>


MainMenuPage::MainMenuPage() : MainMenuPage(nullptr)
{
}

MainMenuPage::MainMenuPage(Student* userPtr)
{
   this->userPtr = userPtr;
}

void MainMenuPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayOptions();

   std::cout << promptOffset;
   savePromptLocation();
   displayPrompt(Prompt::menuOptionSelect);
}

