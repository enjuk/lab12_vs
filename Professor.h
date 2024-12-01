#ifndef PROFESSOR_H_
#define PROFESSOR_H_

#include "Enums.h"

class Professor {
public:
   Professor();
   Professor(ProfessorName nameEnum);
   Professor(ProfessorName nameEnum, int totalPoints, int numSubmissions);
   Professor(const std::string& firstName, const std::string& lastName,
         int totalPoints, int numSubmissions);

   void addCourse(CourseName courseName);
   void display() const;

   void setFirstName(const std::string& firstName);
   void setLastName(const std::string& lastName);
   void addNewRating(int rating);

   ProfessorName getNameEnum() const;
   std::string getFirstName() const;
   std::string getLastName() const;
   int getTotalPoints() const;
   int getNumSubmissions() const;
   double getRating() const;
   std::vector<CourseName> getCourses() const;

private:
   ProfessorName nameEnum;
   std::string firstName;
   std::string lastName;
   int totalPoints;
   int numSubmissions;
   std::vector<CourseName> courses;
};

#endif
