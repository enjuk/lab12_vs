#include "LoginPage.h"
#include "TUI.hpp"
#include <iostream>


LoginPage::LoginPage() : LoginPage(nullptr)
{
}

/* LoginPage::LoginPage(Student* userPtr) */
/* { */
/*    this->userPtr = userPtr; */
/* } */

LoginPage::LoginPage(StudentTable* studentMapPtr)
{
   this->studentMapPtr = studentMapPtr;
}

void LoginPage::display()
{
   tui::clearScreen();
   displayHeader();
   std::cout << promptOffset;
   savePromptLocation();
}

Student* LoginPage::getStudent() const
{
   int studentID = -1;
   bool validInput = false;

   while (!validInput)
   {
      displayPrompt(Prompt::studentID);

      std::string userInput;
      std::getline(std::cin, userInput);

      if (userInput == "cancel")
         return nullptr;
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

            if (!isValidStudentID(studentID)){
               /* displayError(Error::invalidID, 2); */
               /* displayMessage(Message::tryAgainOrCancel); */
               displayError(toString(Error::invalidID),
                     toString(Message::tryAgainOrCancel));
            }
            else if (studentMapPtr->contains(studentID))
            {
               return studentMapPtr->getStudent(studentID);
            }
            else
            {
               /* displayError(Error::noAccountFound, 2); */
               /* displayMessage(Message::tryAgainOrCancel); */
               displayError(toString(Error::noAccountFound),
                     toString(Message::tryAgainOrCancel));
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

   clearAllFeedback();

   return nullptr;
}
