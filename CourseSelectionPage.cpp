#include "CourseSelectionPage.h"
#include "CourseTable.h"
#include "TUI.hpp"
#include <iostream>


CourseSelectionPage::CourseSelectionPage() : CourseSelectionPage(nullptr, nullptr)
{
}

CourseSelectionPage::CourseSelectionPage(Student* userPtr,
      CourseTable* coursesPtr)
{
   this->userPtr = userPtr;
   this->coursesPtr = coursesPtr;

   setOptions();
}

void CourseSelectionPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayOptions();

   std::cout << promptOffset;
   savePromptLocation();
   displayPrompt(Prompt::menuOptionSelect);
}

int CourseSelectionPage::getOptionChoice() const
{
   if (userPtr->getCourseDataVector().empty())
      return Page::getOptionChoice();

   int optionChoice = -1;
   bool validInput = false;

   while (!validInput)
   {
      optionChoice = Page::getOptionChoice();
      CourseName courseChoice = coursesPtr->getEntries()[optionChoice - 1].first;
      validInput = true;

      for (const auto& courseData : userPtr->getCourseDataVector())
      {
         if (courseChoice == courseData.course)
         {
            std::string message = toString(Error::alreadyRegisteredForCourse);
            message += toString(courseChoice);
            displayError(message, toString(Message::tryAgain));
            displayPrompt(Prompt::menuOptionSelect);
            validInput = false;
            break;
         }
      }
   }

   return optionChoice;
}

void CourseSelectionPage::setOptions()
{
   for (int i = 0; i < coursesPtr->getEntries().size(); ++i)
   {
      std::string courseName = toString(coursesPtr->getEntries()[i].first);
      options.insert(std::make_pair(i + 1, courseName));
   }
}

