#ifndef LANDING_PAGE_H_
#define LANDING_PAGE_H_

#include "Page.h"

class LandingPage : public Page {
public:
   LandingPage();
   LandingPage(const std::string& userInfo);
   LandingPage(Student* userPtr);
   void display() override;

private:
   std::string pageDescription = "Landing page";
   optionMap options = {
      { 1, "Login" },
      { 2, "Register" },
      { 3, "Exit" }
   };

   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}

};

#endif
