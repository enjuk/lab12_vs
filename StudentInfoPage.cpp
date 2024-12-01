#include "StudentInfoPage.h"
#include "TUI.hpp"
#include <ios>
#include <iostream>
#include <iomanip>


StudentInfoPage::StudentInfoPage(Student* userPtr, ProfessorTable* professorTable)
{
   this->userPtr = userPtr;
   this->professorTable = professorTable;
}

void StudentInfoPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayTableHeader();
   displayStudentInfo();

   std::cout << promptOffset;
   savePromptLocation();
   pauseWithMessage(toString(Message::returnToMainMenu));
}

void StudentInfoPage::displayStudentInfo() const
{
   const std::vector<StudentCourseData>& courseData = userPtr->getCourseDataVector();
   for (const auto& entry : courseData)
   {
      CourseName courseName = entry.course;
      ProfessorName professorName = entry.professor;
      bool alreadyRated = entry.alreadyRated;

      const Professor* professor = professorTable->getProfessor(professorName);
      std::string professorInfo = " ";
      professorInfo += professor->getFirstName()[0];
      professorInfo += ". " + professor->getLastName();

      std::cout << tableOffset_x << std::left << " " << std::setw(13) << toString(courseName)
         << std::left << std::setw(30) << professorInfo
         << std::right << (alreadyRated ? "Yes" : "No") << std::endl;
   }
}

void StudentInfoPage::displayTableHeader() const
{
   std::string courseLabel = tui::customizeStr("Course", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::string professorLabel = tui::customizeStr("Professor", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::string ratingLabel = tui::customizeStr("Rating Submitted", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::cout << tableOffset_x << " " << courseLabel << "        " << professorLabel
      << "             " << ratingLabel << "\n"
      << tableOffset_x << " ------        ------------          ----------------\n";
}
