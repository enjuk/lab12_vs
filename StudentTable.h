#ifndef STUDENT_TABLE_H_
#define STUDENT_TABLE_H_

#include "Student.h"

struct StudentEntry
{
   int key;
   Student student;

   StudentEntry(int key, const Student& student) : key(key), student(student) {}
};

struct StudentNode {
   StudentEntry entry;
   StudentNode* next;

   StudentNode(StudentEntry entry, StudentNode* next) : entry(entry), next(next) {}
};

class StudentTable {
public:
   StudentTable();
   /* void addEntry(const std::pair<int, Student>& entry); */
   void addEntry(const StudentEntry& entry);
   void display() const;
   bool contains(int targetKey) const;
   Student* getStudent(int key) const;
   void saveToFile(const std::string& fileName) const;
private:
   int numEntries;
   int tableSize = 25013;
   std::vector<StudentNode*> entries;

   int hashValue(int key) const;
};

#endif
