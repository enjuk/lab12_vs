#ifndef COURSE_TABLE_H_
#define COURSE_TABLE_H_

#include "Enums.h"

class CourseTable {
public:
   CourseTable();

   void addEntry(CourseName courseName,
         const std::vector<ProfessorName>& professors);
   
   void display() const;
   
   std::vector<std::pair<CourseName, std::vector<ProfessorName>>> getEntries() const;

private:
   std::vector<std::pair<CourseName, std::vector<ProfessorName>>> entries;
};


#endif
