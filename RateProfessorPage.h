#ifndef RATE_PROFESSOR_PAGE_H_
#define RATE_PROFESSOR_PAGE_H_

#include "Page.h"
#include "ProfessorTable.h"

class RateProfessorPage : public Page {
public:
   RateProfessorPage();
   RateProfessorPage(Student* userPtr, ProfessorTable* professorTable);

   void display() override;
   void displayWithoutBody() const;
   int getOptionChoice() const override;
   int getRating(const std::string& profName) const;

private:
   Student* userPtr;
   ProfessorTable* professorTable;
   std::string pageDescription = "Rate a professor";
   const std::string tableOffset_x = "    "; 

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}
   void displayTableHeader() const;

   void setOptions();

};

#endif
