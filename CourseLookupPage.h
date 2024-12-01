#ifndef COURSE_LOOKUP_PAGE_H_
#define COURSE_LOOKUP_PAGE_H_

#include "Page.h"
#include "CourseTable.h"
#include "ProfessorTable.h"

class CourseLookupPage : public Page {
public:
   CourseLookupPage();
   CourseLookupPage(Student* userPtr, CourseTable* coursesPtr);
   void display() override;

   /* int getOptionChoice() const override; */

private:
   Student* userPtr;
   ProfessorTable* professorsPtr;
   CourseTable* coursesPtr;
   std::string pageDescription = "Look up course information";
   optionMap options;

   void setOptions();

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}

};

#endif
