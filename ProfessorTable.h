#ifndef PROFESSOR_TABLE_H_
#define PROFESSOR_TABLE_H_

#include "Professor.h"

struct ProfessorEntry {
   ProfessorName key;
   Professor professor;

   ProfessorEntry(const Professor& professor)
      : professor(professor)
   {
      key = professor.getNameEnum();
   }
};

struct ProfessorNode {
   ProfessorEntry entry;
   ProfessorNode* next;

   ProfessorNode(ProfessorEntry entry, ProfessorNode* next)
      : entry(entry), next(next) {}
};

class ProfessorTable {
public:
   ProfessorTable();

   void addEntry(const ProfessorEntry& entry);
   void display() const;
   bool contains(ProfessorName targetKey) const;
   Professor* getProfessor(ProfessorName key) const;

   std::vector<ProfessorName> getProfessorNames() const;
   void addProfessorName(ProfessorName professorName);

   void saveToFile(const std::string& fileName);

private:
   int numEntries;
   int tableSize = 23;
   std::vector<ProfessorName> professorNames;
   std::vector<ProfessorNode*> entries;

   int hashValue(ProfessorName key) const;
};


#endif
