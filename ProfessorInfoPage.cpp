#include "ProfessorInfoPage.h"
#include "TUI.hpp"
#include <ios>
#include <iostream>
#include <iomanip>


ProfessorInfoPage::ProfessorInfoPage() : ProfessorInfoPage(nullptr, nullptr)
{
}

ProfessorInfoPage::ProfessorInfoPage(Student* userPtr, Professor* professorPtr)
{
   this->userPtr = userPtr;
   this->professorPtr = professorPtr;

   std::string profDescription;
   profDescription += professorPtr->getFirstName()[0];
   profDescription += ". " + professorPtr->getLastName();

   pageDescription = "Professor info for " + profDescription;
}

void ProfessorInfoPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayProfessorInfo();

   std::cout << promptOffset;
   savePromptLocation();
   pauseWithMessage(toString(Message::returnToMainMenu));
}

void ProfessorInfoPage::displayProfessorInfo() const
{
   std::string profName = professorPtr->getFirstName() + " " +
      professorPtr->getLastName();

   std::cout << std::fixed << std::setprecision(1)
      << labelOffset_x << tui::customizeStr("Name    : ", tui::ColorFG::cyan, tui::Mode::bold)
      << profName << "\n"
      << labelOffset_x << tui::customizeStr("Rating  : ", tui::ColorFG::cyan, tui::Mode::bold)
      << professorPtr->getRating() << "\n\n"
      << labelOffset_x << tui::customizeStr("Courses : ", tui::ColorFG::cyan, tui::Mode::bold);

   const std::vector<CourseName>& courses = professorPtr->getCourses();

   if (courses.empty())
      std::cout << "None" << std::endl;
   else
   {
      std::cout << toString(courses[0]) << "\n";
      for (int i = 1; i < courses.size(); ++i)
         std::cout << labelOffset_x << "          " << toString(courses[i]) << "\n";
   }

   std::cout << std::scientific << std::endl;
}
