#include "ProfessorLookupPage.h"
#include "TUI.hpp"
#include <iostream>


ProfessorLookupPage::ProfessorLookupPage() : ProfessorLookupPage(nullptr, nullptr)
{
}

ProfessorLookupPage::ProfessorLookupPage(Student* userPtr,
      ProfessorTable* professorsPtr)
{
   this->userPtr = userPtr;
   this->professorsPtr = professorsPtr;

   setOptions();
}

void ProfessorLookupPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayOptions();

   std::cout << promptOffset;
   savePromptLocation();
   displayPrompt(Prompt::menuOptionSelect);
}

/* int ProfessorLookupPage::getOptionChoice() const */
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

void ProfessorLookupPage::setOptions()
{
   for (int i = 0; i < professorsPtr->getProfessorNames().size(); ++i)
   {
      ProfessorName professorName = professorsPtr->getProfessorNames()[i];
      const Professor* professor = professorsPtr->getProfessor(professorName);
      std::string profInfo;
      profInfo += professor->getFirstName()[0];
      profInfo += ". " + professor->getLastName();
      options.insert(std::make_pair(i + 1, profInfo));
   }
}

/* int ProfessorTable::getNumEntries() const */
/* { */
/*    return numEntries; */
/* } */
