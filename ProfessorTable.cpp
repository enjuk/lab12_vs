#include "ProfessorTable.h"
#include <iostream>
#include <fstream>

ProfessorTable::ProfessorTable() : numEntries(0), entries(tableSize, nullptr)
{
}

void ProfessorTable::addEntry(const ProfessorEntry& entry)
{
   int index = hashValue(entry.key);
   ProfessorNode* previousHead = entries[index];
   
   ProfessorNode* newHead = new ProfessorNode(entry, previousHead);
   entries[index] = newHead;
   ++numEntries;
}

void ProfessorTable::display() const
{
   for (const auto& head : entries)
   {
      if (head != nullptr)
      {
         ProfessorNode* current = head;

         while (current != nullptr)
         {
            current->entry.professor.display();
            current = current->next;
         }

         std::cout << std::endl;
      }
   }
}

bool ProfessorTable::contains(ProfessorName targetKey) const
{
   int index = hashValue(targetKey);
   ProfessorNode* current = entries[index];

   while (current != nullptr)
   {
      if (current->entry.key == targetKey)
         return true;

      current = current->next;
   }

   return false;
}

Professor* ProfessorTable::getProfessor(ProfessorName key) const
{
   int index = hashValue(key);
   ProfessorNode* current = entries[index];

   while (current != nullptr)
   {
      if (current->entry.key == key)
         return &current->entry.professor;

      current = current->next;
   }

   return nullptr;
}

std::vector<ProfessorName> ProfessorTable::getProfessorNames() const
{
   return professorNames;
}

void ProfessorTable::addProfessorName(ProfessorName professorName)
{
   professorNames.push_back(professorName);
}

void ProfessorTable::saveToFile(const std::string& fileName)
{
   std::ofstream fout(fileName.c_str(), std::ofstream::trunc);
   fout << std::flush;

   for (auto current : entries)
   {
      while (current != nullptr)
      {
         const Professor& professor = current->entry.professor;
         fout << professor.getLastName() << ","
            << professor.getFirstName() << ","
            << professor.getTotalPoints() << ","
            << professor.getNumSubmissions() << ",";

         fout << "\n";
         current = current->next;
      }
   }

   fout.close();
}

int ProfessorTable::hashValue(ProfessorName key) const
{
   std::string keyStr = toString(key);
   int asciiSum = 0;

   for (char c : keyStr)
      asciiSum += static_cast<int>(c);

   return asciiSum % tableSize;
}

