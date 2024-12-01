#include "CourseTable.h"
#include "Enums.h"
#include <iostream>

CourseTable::CourseTable()
{
}

void CourseTable::addEntry(CourseName courseName,
      const std::vector<ProfessorName>& professors)
{
   entries.push_back(std::make_pair(courseName, professors)); 
}

void CourseTable::display() const
{
   for (const auto& [courseName, professors] : entries)
   {
      std::cout << toString(courseName) << "\n";
   
      for (const auto& professorName : professors)
      {
         std::cout << "\t" << toString(professorName) << "\n";
      }
   }
   
   std::cout << std::endl;
}

std::vector<std::pair<CourseName, std::vector<ProfessorName>>>
   CourseTable::getEntries() const
{
   return entries;
}
