#include "RegisterProfessorSelectPage.h"
#include "TUI.hpp"
#include <ios>
#include <iostream>
#include <iomanip>
#include <sstream>


RegisterProfessorSelectPage::RegisterProfessorSelectPage(Student* userPtr,
      CourseName courseName, const std::vector<Professor*>& professors)
{
   this->userPtr = userPtr;
   this->courseName = courseName;
   this->professors = professors;

   pageDescription = "Registration - professor selection for "
      + toString(courseName);

   setOptions();
}

void RegisterProfessorSelectPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayTableHeader();
   displayOptions(tableOffset_x);

   std::cout << promptOffset;
   savePromptLocation();
   displayPrompt(Prompt::menuOptionSelect);
}

void RegisterProfessorSelectPage::displayWithoutBody()
{
   tui::clearScreen();
   displayHeader();
}

/* void RegisterProfessorSelectPage::displayTableHeader() const */
/* { */
/*    std::cout << "      Professor                      Rating\n" */
/*              << "      -------------------------------------\n"; */
/* } */

void RegisterProfessorSelectPage::displayTableHeader() const
{
   std::string optionLabel = tui::customizeStr("Option", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::string professorLabel = tui::customizeStr("Professor", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::string ratingLabel = tui::customizeStr("Rating", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::cout << tableOffset_x << "  " << optionLabel << "     " 
      << professorLabel << "                 " << ratingLabel << "\n"
      << tableOffset_x << "  ------     ---------                --------\n";
      /* << " -------------------------------------------------------------\n"; */
      /* << " =============================================================\n"; */
}

void RegisterProfessorSelectPage::setOptions()
{
   for (int i = 0; i < professors.size(); ++i)
   {
      const Professor* professor = professors[i];
      std::string professorInfo;
      professorInfo += professor->getFirstName()[0];
      professorInfo += ". " + professor->getLastName();

      std::ostringstream oss;
      oss << "      " << std::left << std::setw(24) << professorInfo
          << std::right << std::fixed << std::setprecision(1)
          << std::setw(6) << professor->getRating() << std::setprecision(6) << std::scientific;

      options.insert(std::make_pair(i + 1, oss.str()));
   }
}

