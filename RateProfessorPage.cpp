#include "RateProfessorPage.h"
#include "TUI.hpp"
#include <ios>
#include <iostream>
#include <iomanip>
#include <sstream>


RateProfessorPage::RateProfessorPage(Student* userPtr, ProfessorTable* professorTable)
{
   this->userPtr = userPtr;
   this->professorTable = professorTable;
}

void RateProfessorPage::display()
{
   tui::clearScreen();
   displayHeader();
   displayTableHeader();
   setOptions();
   displayOptions(tableOffset_x);

   std::cout << promptOffset;
   savePromptLocation();
   displayPrompt(Prompt::menuOptionSelect);
}

void RateProfessorPage::displayWithoutBody() const
{
   tui::clearScreen();
   displayHeader();
}

void RateProfessorPage::setOptions()
{
   options.clear();
   const std::vector<StudentCourseData>& courseData = userPtr->getCourseDataVector();
   for (int i = 0; i < courseData.size(); ++i)
   {
      CourseName courseName = courseData[i].course;
      ProfessorName professorName = courseData[i].professor;
      bool alreadyRated = courseData[i].alreadyRated;

      const Professor* professor = professorTable->getProfessor(professorName);
      std::string professorInfo = " ";
      professorInfo += professor->getFirstName()[0];
      professorInfo += ". " + professor->getLastName();

      std::ostringstream oss;
      oss << "      " << std::left << std::setw(13) << toString(courseName)
         << std::left << std::setw(30) << professorInfo
         << std::right << (alreadyRated ? "Yes" : "No");

      options.insert(std::make_pair(i + 1, oss.str()));
   }
}

void RateProfessorPage::displayTableHeader() const
{
   std::string optionLabel = tui::customizeStr("Option", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::string courseLabel = tui::customizeStr("Course", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::string professorLabel = tui::customizeStr("Professor", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::string ratingLabel = tui::customizeStr("Rating Submitted", tui::ColorFG::cyan,
         tui::Mode::bold);

   std::cout << tableOffset_x << "  " << optionLabel << "     "<< courseLabel << "        "
      << professorLabel << "             " << ratingLabel << "\n"
      << tableOffset_x << "  ------     ------        ---------             ----------------\n";
}

int RateProfessorPage::getOptionChoice() const
{
   int optionChoice = -1;
   bool validInput = false;

   while (!validInput)
   {
      optionChoice = Page::getOptionChoice();
      StudentCourseData data = userPtr->getCourseDataVector()[optionChoice - 1];

      if (data.alreadyRated)
      {
         std::string message = toString(Error::alreadySubmittedRating);
         message += toString(data.course);
         displayError(message, toString(Message::tryAgain));
         displayPrompt(Prompt::menuOptionSelect);
      }
      else
         validInput = true;
   }

   return optionChoice;
}

int RateProfessorPage::getRating(const std::string& profName) const
{
   /* displayWithoutBody(); */
   clearAllFeedback();
   displayInstructions(Message::ratingInstructions);

   int optionChoice = -1;
   bool validInput = false;

   while (!validInput)
   {
      std::string prompt = toString(Prompt::ratingForCourse);
      prompt += profName;
      displayPrompt(prompt);

      std::string userInput;
      std::getline(std::cin, userInput);

      if (!containsOnlyNumeric(userInput))
      {
         displayError(toString(Error::invalidRating),
               toString(Message::ratingInstructions));
      }
      else
      {
         try
         {
            optionChoice = std::stoi(userInput);

            if (optionChoice >= 1 && optionChoice <= 5)
            {
               validInput = true;
            }
            else
            {
               displayError(toString(Error::invalidRating),
                     toString(Message::ratingInstructions));
            }
         }
         catch (const std::exception&)
         {
            displayError(toString(Error::invalidRating),
                  toString(Message::ratingInstructions));
         }
      }
   }

   return optionChoice; 
}
