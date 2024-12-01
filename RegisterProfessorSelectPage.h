#ifndef REGISTER_PROFESSOR_SELECT_PAGE_H_
#define REGISTER_PROFESSOR_SELECT_PAGE_H_

#include "Page.h"
#include "Professor.h"

class RegisterProfessorSelectPage : public Page {
public:
   RegisterProfessorSelectPage();
   RegisterProfessorSelectPage(Student* userPtr,  CourseName courseName,
         const std::vector<Professor*>& professors);
   void display() override;
   void displayWithoutBody();

private:
   Student* userPtr;
   std::vector<Professor*> professors;
   CourseName courseName;
   std::string pageDescription;
   const std::string tableOffset_x = "    "; 
   optionMap options;

   void displayTableHeader() const;
   void setOptions();

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}

};

#endif
