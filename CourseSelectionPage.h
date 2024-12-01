#ifndef COURSE_SELECTION_PAGE_H_
#define COURSE_SELECTION_PAGE_H_

#include "Page.h"
#include "CourseTable.h"

class CourseSelectionPage : public Page {
public:
   CourseSelectionPage();
   CourseSelectionPage(Student* userPtr, CourseTable* coursesPtr);
   void display() override;

   int getOptionChoice() const override;

private:
   Student* userPtr;
   CourseTable* coursesPtr;
   std::string pageDescription = "Registration - course selection";
   optionMap options;

   void setOptions();

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
   optionMap getOptions() const override {return options;}

};

#endif
