#include "RegisterAccountPage.h"
#include "TUI.hpp"
#include <iostream>

RegisterAccountPage::RegisterAccountPage() : Page()
{
}

RegisterAccountPage::RegisterAccountPage(StudentTable* studentMapPtr)
{
   this->userPtr = nullptr;
   this->studentMapPtr = studentMapPtr;
}

void RegisterAccountPage::display()
{
   tui::clearScreen();
   displayHeader();
   std::cout << promptOffset;
   savePromptLocation();
}

Student RegisterAccountPage::getStudent()
{
   Student newStudent;
   newStudent.setID(getStudentID());

   if (newStudent.getID() != -1)
   {
      newStudent.setFirstName(getFirstName());
      newStudent.setLastName(getLastName());
   }

   return newStudent;
}

int RegisterAccountPage::getStudentID()
{
   int studentID = -1;
   bool validInput = false;

   while (!validInput)
   {
      displayPrompt(Prompt::studentID);

      std::string userInput;
      std::getline(std::cin, userInput);

      if (userInput == "cancel")
         return -1;
      else if (!containsOnlyNumeric(userInput))
      {
         /* displayError(Error::invalidID, 2); */
         /* displayMessage(Message::tryAgainOrCancel); */
         displayError(toString(Error::invalidID),
               toString(Message::tryAgainOrCancel));
      }
      else
      {
         try
         {
            studentID = std::stoi(userInput);

            if (!isValidStudentID(studentID))
            {
               /* displayError(Error::invalidID, 2); */
               /* displayMessage(Message::tryAgainOrCancel); */
               displayError(toString(Error::invalidID),
                     toString(Message::tryAgainOrCancel));
            }
            else if (studentMapPtr->contains(studentID))
            {
               /* displayError(Error::accountAlreadyExists, 2); */
               /* displayMessage(Message::tryAgainOrCancel); */
               displayError(toString(Error::accountAlreadyExists),
                     toString(Message::tryAgainOrCancel));
            }
            else
            {
               return studentID;
            }
         }
         catch (const std::exception&)
         {
            /* displayError(Error::invalidID, 2); */
            /* displayMessage(Message::tryAgainOrCancel); */
            displayError(toString(Error::invalidID),
                  toString(Message::tryAgainOrCancel));
         }
      }
   }

   return -1;
}

std::string RegisterAccountPage::getFirstName()
{
   clearAllFeedback();
   displayPrompt(Prompt::studentFirstName);

   std::string firstName;
   std::getline(std::cin, firstName);

   return firstName;
}

std::string RegisterAccountPage::getLastName()
{
   clearAllFeedback();
   displayPrompt(Prompt::studentLastName);

   std::string lastName;
   std::getline(std::cin, lastName);

   return lastName;
}
