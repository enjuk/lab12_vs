#ifndef STUDENT_INFO_PAGE_H_
#define STUDENT_INFO_PAGE_H_

#include "Page.h"
#include "ProfessorTable.h"

class StudentInfoPage : public Page {
public:
   StudentInfoPage();
   StudentInfoPage(Student* userPtr, ProfessorTable* professorTable);

   void display() override;

private:
   Student* userPtr;
   ProfessorTable* professorTable;
   std::string pageDescription = "Registered courses";
   std::string tableOffset_x = "    ";

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}
   void displayTableHeader() const;

   void displayStudentInfo() const;
};

#endif
