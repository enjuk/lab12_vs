#ifndef PROFESSOR_LOOKUP_PAGE_H_
#define PROFESSOR_LOOKUP_PAGE_H_

#include "Page.h"
#include "ProfessorTable.h"

class ProfessorLookupPage : public Page {
public:
   ProfessorLookupPage();
   ProfessorLookupPage(Student* userPtr, ProfessorTable* professorsPtr);
   void display() override;

   /* int getOptionChoice() const override; */

private:
   Student* userPtr;
   ProfessorTable* professorsPtr;
   std::string pageDescription = "Look up professor information";
   optionMap options;

   void setOptions();

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}

};

#endif
