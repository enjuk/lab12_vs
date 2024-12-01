#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include "Enums.h"

struct StudentCourseData {
   CourseName course;
   ProfessorName professor;
   bool alreadyRated;

   StudentCourseData(CourseName course, ProfessorName professor, bool alreadyRated)
      : course(course), professor(professor), alreadyRated(alreadyRated) {}
};


class Student {
public:
   Student();
   Student(int id, const std::string& firstName, const std::string& lastName);

   void loadCourse(std::pair<CourseName, ProfessorName> courseProfPair);
   void loadCourse(StudentCourseData);

   void setID(int id);
   void setFirstName(const std::string& firstName);
   void setLastName(const std::string& lastName);
   void submitRatingForIndex(int index);

   int getID() const;
   std::string getFirstName() const;
   std::string getLastName() const;
   std::vector<std::pair<CourseName, ProfessorName>> getCourses() const;
   std::vector<StudentCourseData> getCourseDataVector() const;

   std::string getInfo() const;
   void display();

private:
   int id;
   std::string firstName;
   std::string lastName;
   std::vector<std::pair<CourseName, ProfessorName>> courses;

   std::vector<StudentCourseData> courseDataVector;

};

#endif

