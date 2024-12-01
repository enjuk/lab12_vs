#ifndef PAGE_H_
#define PAGE_H_

#include <map>
#include <string>
#include "Student.h"

using optionMap = std::map<int, std::string>;

enum class Error {
   invalidMenuOption, noAccountFound, invalidID, accountAlreadyExists,
   alreadyRegisteredForCourse, alreadySubmittedRating, invalidRating
};

inline std::string toString(Error error)
{
   switch(error)
   {
      case Error::invalidMenuOption:
         return "NOT A VALID MENU OPTION";

      case Error::noAccountFound:
         return "NO ACCOUNT EXISTS FOR THAT ID";

      case Error::invalidID:
         return "NOT A VALID STUDENT ID";

      case Error::accountAlreadyExists:
         return "AN ACCOUNT FOR THAT ID IS ALREADY REGISTERED";

      case Error::alreadyRegisteredForCourse:
         return "YOU ARE ALREADY REGISTERED FOR ";

      case Error::alreadySubmittedRating:
         return "YOU HAVE ALREADY SUBMITTED A RATING FOR ";

      case Error::invalidRating:
         return "NOT A VALID RATING ";

      default:
         return "INVALID ENUM TO STRING CONVERSION";
   }

   return "Invalid Enum Member";
}

enum class Message {
   tryAgain, tryAgainOrCancel, registerSuccess, ratingInstructions, ratingSuccess,
   returnToMainMenu
};

inline std::string toString(Message message)
{
   switch(message)
   {
      case Message::tryAgain:
         return "Try again";

      case Message::tryAgainOrCancel:
         return "Try again or type \"cancel\" to go back";

      case Message::registerSuccess:
         return "COURSE REGISTRATION SUCCESSFUL";

      case Message::ratingInstructions:
         return "Rate on a scale of 1-5 (whole numbers only)";

      case Message::ratingSuccess:
         return "RATING SUBMISSION SUCCESSFUL";

      case Message::returnToMainMenu:
         return "Press any key to return to main menu . . .";

      default:
         return "INVALID ENUM TO STRING CONVERSION";
   }

   return "Invalid Enum Member";
}

enum class Prompt {
   menuOptionSelect, studentID, studentFirstName, studentLastName,
   ratingForCourse
};

inline std::string toString(Prompt prompt)
{
   switch(prompt)
   {
      case Prompt::menuOptionSelect:
         return "Select a menu option";

      case Prompt::studentID:
         return "Enter your student ID";

      case Prompt::studentFirstName:
         return "Enter your first name";

      case Prompt::studentLastName:
         return "Enter your last name";

      case Prompt::ratingForCourse:
         return "Enter your rating for ";

      default:
         return "INVALID ENUM TO STRING CONVERSION";
   }

   return "Invalid Enum Member";
}

class Page {
   public:
      void displayMessage(Message message) const;
      void displayInstructions(Message message) const;

      void displaySuccess(const std::string& line1,
            const std::string& line2 = "") const;

      void displayError(const std::string& line1,
            const std::string& line2 = "") const;

      bool isValidStudentID(int studentID) const;
      void hidePrompt() const;
      void pauseWithMessage(const std::string& message);

      virtual void display() = 0;
      virtual int getOptionChoice() const;

   protected:
      Student* userPtr = nullptr;
      std::string pageDescription = "N/A";
      const std::string promptOffset = "\n\n\n\n\n\n";
      const std::string promptOffset_x = "  ";
      const std::string tableOffset_x = "       ";
      optionMap options;

      virtual Student* getUserPtr() const {return userPtr;}
      virtual std::string getPageDescription() const {return pageDescription;}
      virtual optionMap getOptions() const {return options;}

      /* void displayHeader(const std::string& studentInfo); */
      void displayHeader() const;

      void displayOptions(const std::string& offset_x = "") const;
      void displayPrompt(Prompt prompt) const;
      void displayPrompt(const std::string& prompt) const;
      std::string formatOptionNumber(int num) const;
      void savePromptLocation() const;
      void restorePromptLocation() const;
      void clearAllFeedback() const;
      bool containsOnlyNumeric(const std::string& str) const;
};

#endif
