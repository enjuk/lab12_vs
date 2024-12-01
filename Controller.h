#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Student.h"
#include "StudentTable.h"
#include "CourseTable.h"
#include "ProfessorTable.h"

class Controller {
public:
   Controller();
   ~Controller();

   // The only page that needs to be public as it's called from main.
   // The rest of pages are called locally.
   void processLandingPage();

private:
   Student* user;
   StudentTable studentTable;
   CourseTable courseTable;
   ProfessorTable professorTable;

   // Loading data from files into data members
   void loadStudentTable();
   void loadCourses();
   void loadProfessorTable();
   void addCoursesToProfessorTable();

   // Controlling pages (which are responsible for input / output)
   void processLoginPage();
   void processRegisterAccountPage();
   void processMainMenuPage();
   void processCourseSelectionPage();
   void processRegisterProfessorSelectPage(CourseName course);
   void processProfessorLookupPage();
   void processProfessorInfoPage(Professor* professorPtr);
   void processCourseLookupPage();
   void processCourseInfoPage(CourseName courseName,
         std::vector<ProfessorName> professorNames);
   void processStudentInfoPage();
   void processRateProfessorPage();
};

#endif
