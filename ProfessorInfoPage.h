#ifndef PROFESSOR_INFO_PAGE_H_
#define PROFESSOR_INFO_PAGE_H_

#include "Page.h"
#include "Professor.h"

class ProfessorInfoPage : public Page {
public:
   ProfessorInfoPage();
   ProfessorInfoPage(Student* userPtr, Professor* professorPtr);
   void display() override;

private:
   Student* userPtr;
   Professor* professorPtr;
   std::string pageDescription;
   std::string labelOffset_x = "  ";

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}

   void displayProfessorInfo() const;

};

#endif
