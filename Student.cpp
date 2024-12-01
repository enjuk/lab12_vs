#include "Student.h"
#include <iostream>

Student::Student() : Student(-1, "N/A", "N/A")
{
}

Student::Student(int id, const std::string& firstName, const std::string& lastName)
   : id(id), firstName(firstName), lastName(lastName)
{
}

void Student::loadCourse(std::pair<CourseName, ProfessorName> courseProfPair)
{
   courses.push_back(courseProfPair);
}



void Student::loadCourse(StudentCourseData courseData)
{
   courseDataVector.push_back(courseData);
}



void Student::setID(int id)
{
   this->id = id;
}

void Student::setFirstName(const std::string& firstName)
{
   this->firstName = firstName;
}

void Student::setLastName(const std::string& lastName)
{
   this->lastName = lastName;
}

void Student::submitRatingForIndex(int index)
{
   courseDataVector[index].alreadyRated = true;
}

int Student::getID() const {
   return id;
}

std::string Student::getFirstName() const
{
   return firstName;
}

std::string Student::getLastName() const
{
   return lastName;
}

/* std::vector<std::pair<CourseName, ProfessorName>> Student::getCourses() const */
/* { */
/*    return courses; */
/* } */

std::vector<StudentCourseData> Student::getCourseDataVector() const
{
   return courseDataVector;
}

std::string Student::getInfo() const
{
   return firstName + " " + lastName + " (" + std::to_string(id) + ")";
}

/* void Student::display() */
/* { */
/*    std::cout << getInfo() << "\n"; */
/*  */
/*    for (const auto& course : courses) */
/*    { */
/*       std::cout << toString(course.first) << ", " */
/*          << toString(course.second) << "\n"; */
/*    } */
/*  */
/*    std::cout << std::endl; */
/* } */

void Student::display()
{
   std::cout << "\t" << getInfo() << "\n";

   for (const auto& courseData : courseDataVector)
   {
      std::cout << "\t  - " << toString(courseData.course) << ", "
         << toString(courseData.professor) << ", "
         << (courseData.alreadyRated ? "Rated" : "No Rating") << "\n";
   }

   std::cout << std::endl;
}






