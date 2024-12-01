#include "CourseInfoPage.h"
#include "TUI.hpp"
#include <ios>
#include <iostream>
#include <iomanip>


CourseInfoPage::CourseInfoPage(Student* userPtr, CourseName courseName,
      const std::vector<ProfessorName>& professorNames, ProfessorTable* professorTable)
{
   this->userPtr = userPtr;
   this->courseName = courseName;
   this->professorNames = professorNames;
   this->professorTable = professorTable;

   pageDescription = "Professors teaching " + toString(courseName);
}

void CourseInfoPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayTableHeader();
   displayCourseInfo();

   std::cout << promptOffset;
   savePromptLocation();
   pauseWithMessage(toString(Message::returnToMainMenu));
}

void CourseInfoPage::displayCourseInfo() const
{
   for (const auto& professorName : professorNames)
   {
      const Professor* professor = professorTable->getProfessor(professorName);
      std::string professorInfo = " ";
      professorInfo += professor->getFirstName()[0];
      professorInfo += ". " + professor->getLastName();

      std::cout << tableOffset_x << std::left << std::setw(25) << professorInfo
         << std::right << std::fixed << std::setprecision(1)
         << std::setw(6) << professor->getRating() << std::setprecision(6)
         << std::scientific << std::endl;
   }
}

void CourseInfoPage::displayTableHeader() const
{
   std::string professorLabel = tui::customizeStr("Professor", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::string ratingLabel = tui::customizeStr("Rating", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::cout << tableOffset_x << " " << professorLabel << "                 " << ratingLabel << "\n"
      << tableOffset_x << " ------------              ------\n";
}
