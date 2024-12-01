#include "Enums.h"
#include "Professor.h"
#include <iostream>
#include <sstream>

Professor::Professor() : Professor(ProfessorName::INVALID, -1, 1)
{
}

Professor::Professor(ProfessorName nameEnum, int totalPoints, int numSubmissions)
   : nameEnum(nameEnum), totalPoints(totalPoints), numSubmissions(numSubmissions)
{
   if (nameEnum == ProfessorName::INVALID)
   {
      firstName = "N/A";
      lastName = "N/A";
      totalPoints = -1;
      numSubmissions = 1;
   }
   else
   {
      std::stringstream professorNameStream(toString(nameEnum));
      std::string token;

      std::getline(professorNameStream, token, ',');
      lastName = token;

      std::getline(professorNameStream, token, ',');
      firstName = token;
   }
}

Professor::Professor(const std::string& firstName, const std::string& lastName,
      int totalPoints, int numSubmissions) : firstName(firstName), lastName(lastName)
{
   /* setRating(totalPoints, numSubmissions); */
}

void Professor::addCourse(CourseName courseName)
{
   courses.push_back(courseName);
}

void Professor::setFirstName(const std::string& firstName)
{
   this->firstName = firstName;
}

void Professor::setLastName(const std::string& lastName)
{
   this->lastName = lastName;
}

void Professor::addNewRating(int rating)
{
   totalPoints += rating;
   ++numSubmissions;
}

ProfessorName Professor::getNameEnum() const
{
   return nameEnum;
}

std::string Professor::getFirstName() const
{
   return firstName;
}

std::string Professor::getLastName() const
{
   return lastName;
}

int Professor::getTotalPoints() const
{
   return totalPoints;
}

int Professor::getNumSubmissions() const
{
   return numSubmissions;
}

double Professor::getRating() const {
   return static_cast<double>(totalPoints) / numSubmissions;
}

std::vector<CourseName> Professor::getCourses() const
{
   return courses;
}

void Professor::display() const
{
   std::cout << firstName << " " << lastName << " " << getRating() << "\n";

   for (const auto& course : courses)
   {
      std::cout << "\t" << toString(course) << "\n";
   }

   std::cout << std::endl;
}







