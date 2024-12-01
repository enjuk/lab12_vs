#ifndef COURSE_INFO_PAGE_H_
#define COURSE_INFO_PAGE_H_

#include "Page.h"
#include "ProfessorTable.h"

class CourseInfoPage : public Page {
public:
   CourseInfoPage();
   CourseInfoPage(Student* userPtr, CourseName courseName,
         const std::vector<ProfessorName>& professorNames, ProfessorTable* professorTable);

   void display() override;

private:
   Student* userPtr;
   CourseName courseName;
   ProfessorTable* professorTable;
   std::vector<ProfessorName> professorNames;
   std::string pageDescription;
   std::string tableOffset_x = "    ";

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}
   void displayTableHeader() const;

   void displayCourseInfo() const;

};

#endif
