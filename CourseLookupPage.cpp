#include "CourseLookupPage.h"
#include "TUI.hpp"
#include <iostream>


CourseLookupPage::CourseLookupPage() : CourseLookupPage(nullptr, nullptr)
{
}

CourseLookupPage::CourseLookupPage(Student* userPtr, CourseTable* coursesPtr)
{
   this->userPtr = userPtr;
   this->coursesPtr = coursesPtr;

   setOptions();
}

void CourseLookupPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayOptions();

   std::cout << promptOffset;
   savePromptLocation();
   displayPrompt(Prompt::menuOptionSelect);
}

/* int CourseLookupPage::getOptionChoice() const */
/* { */
/*    int optionChoice = Page::getOptionChoice(); */
/*    ProfessorName professorChoice = professorsPtr->getProfessorNames()[optionChoice - 1]; */
/*  */
/*    for (const auto& courseData : userPtr->getCourseDataVector()) */
/*    { */
/*       if (courseChoice == courseData.course) */
/*       { */
/*          std::string message = toString(Error::alreadyRegisteredForCourse); */
/*          message += toString(courseChoice); */
/*          displayError(message); */
/*          displayPrompt(Prompt::menuOptionSelect); */
/*          validInput = false; */
/*          break; */
/*       } */
/*    } */
/*  */
/*    return optionChoice; */
/* } */

void CourseLookupPage::setOptions()
{
   for (int i = 0; i < coursesPtr->getEntries().size(); ++i)
   {
      CourseName courseName = coursesPtr->getEntries()[i].first;
      options.insert(std::make_pair(i + 1, toString(courseName)));
   }
}

/* int ProfessorTable::getNumEntries() const */
/* { */
/*    return numEntries; */
/* } */
