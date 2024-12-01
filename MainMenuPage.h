#ifndef MAIN_MENU_PAGE_H_
#define MAIN_MENU_PAGE_H_

#include "Page.h"

class MainMenuPage : public Page {
public:
   MainMenuPage();
   MainMenuPage(Student* userPtr);
   void display() override;

private:
   Student* userPtr;
   std::string pageDescription = "Main menu";
   optionMap options = {
      { 1, "Register for course" },
      { 2, "Look up a professor" },
      { 3, "Look up a course" },
      { 4, "Check my courses" },
      { 5, "Rate a professor" },
      { 6, "Exit" }
   };

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}

};

#endif
