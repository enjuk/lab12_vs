#include "Page.h"
#include "TUI.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

void Page::displayMessage(Message message) const
{
   std::string stylizedMessage = tui::customizeStr(toString(message),
      tui::ColorFG::red);

   restorePromptLocation();
   tui::moveCursorUp(1);
   std::cout << promptOffset_x <<stylizedMessage;
}

void Page::displayInstructions(Message message) const
{
   std::string stylizedMessage = tui::customizeStr(toString(message),
      tui::ColorFG::yellow);

   restorePromptLocation();
   tui::moveCursorUp(1);
   std::cout << promptOffset_x <<stylizedMessage;
}

void Page::displaySuccess(const std::string& line1,
      const std::string& line2) const
{
   std::string stylizedMessage1 = tui::customizeStr(line1,
      tui::ColorFG::green, tui::Mode::bold);

   std::string stylizedMessage2;
   int offset = 1;
   if (line2 != "")
   {
      stylizedMessage2 = tui::customizeStr(line2, tui::ColorFG::green);
      ++offset;
   }

   hidePrompt();
   restorePromptLocation();
   tui::moveCursorUp(offset);
   tui::clearLines(offset);
   tui::moveCursorUp(offset);
   std::cout << promptOffset_x << stylizedMessage1 << std::endl;
   std::cout << promptOffset_x <<stylizedMessage2 << std::endl;
   restorePromptLocation();
}

void Page::displayError(const std::string& line1,
      const std::string& line2) const
{
   std::string stylizedMessage1 = tui::customizeStr(line1,
      tui::ColorFG::red, tui::Mode::bold);

   std::string stylizedMessage2;
   int offset = 1;
   if (line2 != "")
   {
      stylizedMessage2 = tui::customizeStr(line2, tui::ColorFG::red);
      ++offset;
   }

   hidePrompt();
   restorePromptLocation();
   tui::moveCursorUp(offset);
   tui::clearLines(offset);
   tui::moveCursorUp(offset);
   std::cout << promptOffset_x << stylizedMessage1 << std::endl;
   std::cout << promptOffset_x <<stylizedMessage2 << std::endl;
   restorePromptLocation();
}

int Page::getOptionChoice() const
{
   int optionChoice = -1;
   bool validInput = false;

   while (!validInput)
   {
      displayPrompt(Prompt::menuOptionSelect);

      std::string userInput;
      std::getline(std::cin, userInput);

      if (!containsOnlyNumeric(userInput))
      {
         displayError(toString(Error::invalidMenuOption),
               toString(Message::tryAgain));
      }
      else
      {
         try
         {
            optionChoice = std::stoi(userInput);

            if (getOptions().contains(optionChoice))
            {
               validInput = true;
            }
            else
            {
               displayError(toString(Error::invalidMenuOption),
                     toString(Message::tryAgain));
            }
         }
         catch (const std::exception&)
         {
            displayError(toString(Error::invalidMenuOption),
                  toString(Message::tryAgain));
         }
      }
   }

   return optionChoice;
}

void Page::displayHeader() const
{
   std::string userInfo;

   if (getUserPtr() == nullptr)
      userInfo = "N/A";
   else
      userInfo = getUserPtr()->getFirstName() + " " + getUserPtr()->getLastName()
         + " (ID# " + std::to_string(getUserPtr()->getID()) + ")";

   userInfo = customizeStr(userInfo, tui::ColorFG::cyan, tui::Mode::bold);
   std::string pageName = customizeStr(getPageDescription(), tui::ColorFG::yellow,
         tui::Mode::italic);

   std::cout << "  ==========================================================================\n";
   std::cout << " |                 Registration for Computer Science Classes                |\n"
             << " |                            Saddleback College                            |\n"
             << " |--------------------------------------------------------------------------|\n"
             << " |  Logged in as: " << std::left << std::setw(67) << userInfo << "     |\n"
             << " |- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |\n"
             << " |  " << std::setw(85) << pageName << "     |\n"
             << "  ==========================================================================\n\n\n"
             << std::right;
}

void Page::displayOptions(const std::string& offset_x) const
{
   for (const auto& [num, option]: getOptions())
   {
      std::cout << promptOffset_x << offset_x << std::setw(22) << formatOptionNumber(num)
         << " " << option << std::endl;
   }
}

std::string Page::formatOptionNumber(int num) const
{
   std::string formattedNum = tui::customizeStr(std::to_string(num),
         tui::ColorFG::cyan, tui::Mode::bold);

   return "<" + formattedNum + ">";
}

bool Page::isValidStudentID(int studentID) const
{
   const int requiredLength = 6;

   if (studentID < pow(10, requiredLength - 1) ||
         studentID > pow(10, requiredLength) -1)
      return false;

   int sum = 0;
   int numerator = studentID;

   for (int i = 0; i < requiredLength; ++i)
   {
      int digit = numerator % 10;

      if (i % 2 == 0)
      {
         digit *= 2;

         if (digit > 9)
            digit -= 9;
      }

      sum += digit;
      numerator /= 10;
   }

   return sum % 10 == 0; 
}

bool Page::containsOnlyNumeric(const std::string& str) const
{
   for (char c : str)
      if (c < 48 || c > 57)
         return false;

   return true;
}

void Page::savePromptLocation() const
{
   tui::saveCursorPosition();
}

void Page::restorePromptLocation() const
{
   tui::restoreCursorPosition();
}

void Page::clearAllFeedback() const
{
   restorePromptLocation();
   tui::moveCursorUp(2);
   tui::clearLines(3);
}

void Page::displayPrompt(Prompt prompt) const
{
   displayPrompt(toString(prompt));
}

void Page::displayPrompt(const std::string& prompt) const
{
   restorePromptLocation();
   tui::clearLine();
   std::string test{" ", 2};
   std::cout << promptOffset_x << customizeStr(prompt, tui::ColorFG::standard,
         tui::Mode::bold) << ": ";
}

void Page::pauseWithMessage(const std::string& message)
{
   std::string fullMessage = promptOffset_x;
   fullMessage += message;

   tui::pauseProgramWithMessage(fullMessage);
}

void Page::hidePrompt() const
{
   restorePromptLocation();
   tui::clearLine();
}
