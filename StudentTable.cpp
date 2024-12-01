#include "StudentTable.h"
#include <iostream>
#include <fstream>

StudentTable::StudentTable() : numEntries(0), entries(tableSize, nullptr)
{
}

void StudentTable::addEntry(const StudentEntry& entry)
{
   int index = hashValue(entry.key);
   StudentNode* previousHead = entries[index];
   
   StudentNode* newHead = new StudentNode(entry, previousHead);
   entries[index] = newHead;
   ++numEntries;
}

void StudentTable::display() const
{
   for (const auto& head : entries)
   {
      if (head != nullptr)
      {
         StudentNode* current = head;

         while (current != nullptr)
         {
            current->entry.student.display();
            current = current->next;
         }

         std::cout << std::endl;
      }
   }
}

bool StudentTable::contains(int targetKey) const
{
   int index = hashValue(targetKey);
   StudentNode* current = entries[index];

   while (current != nullptr)
   {
      if (current->entry.key == targetKey)
         return true;

      current = current->next;
   }

   return false;
}

Student* StudentTable::getStudent(int key) const
{
   int index = hashValue(key);
   StudentNode* current = entries[index];

   while (current != nullptr)
   {
      if (current->entry.key == key)
         return &current->entry.student;

      current = current->next;
   }

   return nullptr;
}

void StudentTable::saveToFile(const std::string& fileName) const
{
   std::ofstream fout(fileName.c_str(), std::ofstream::trunc);
   fout << std::flush;

   for (auto current : entries)
   {
      while (current != nullptr)
      {
         const Student& student = current->entry.student;
         fout << student.getID() << "," << student.getLastName() << ","
            << student.getFirstName() << ",";

         for (const auto& courseData : student.getCourseDataVector())
         {
            fout << toString(courseData.course) << ","
               << toString(courseData.professor) << ","
               << (courseData.alreadyRated ? "true" : "false") << ",";
         }

         fout << "\n";
         current = current->next;
         if (current != nullptr)
            fout << ",";
      }
   }

   fout.close();
}

int StudentTable::hashValue(int key) const
{
   return key % tableSize;
}

