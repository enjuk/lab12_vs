#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Controller.h"
#include "CourseInfoPage.h"
#include "CourseLookupPage.h"
#include "ProfessorTable.h"
#include "Enums.h"
#include "LandingPage.h"
#include "LoginPage.h"
#include "ProfessorInfoPage.h"
#include "ProfessorLookupPage.h"
#include "RateProfessorPage.h"
#include "RegisterAccountPage.h"
#include "MainMenuPage.h"
#include "CourseSelectionPage.h"
#include "RegisterProfessorSelectPage.h"
#include "StudentInfoPage.h"
#include "TUI.hpp"

Controller::Controller()
{
   tui::clearScreen();
   std::cout << "\n";

   // Load student data from data file into studentTable.
   loadStudentTable();
   std::cout << "\n\n";

   // Load course data from data file into courseTable.
   loadCourses();

   // Load professor name and rating data from data file into professorTable.
   // Then, course data is added to each professor from courseTable
   loadProfessorTable();
   addCoursesToProfessorTable();

   tui::pauseProgramWithMessage("\n\nPress any key to proceed to landing page . . .");
}

Controller::~Controller()
{
}

void Controller::loadStudentTable()
{
   std::cout << "Loading student entries from file into StudentTable object...\n\n";

   // Use the File enum to get the correct file name for student data.
   std::ifstream fin(toString(File::studentData).c_str());
   std::string line;
   
   // Go through each line in the file to get each student's id, first name,
   // last name, and information for each course (courseName, profName, ratingSumitted?)
   while(std::getline(fin, line))
   {
      Student student;

      // use stringstream to parse all the student's attibutes for each line
      std::stringstream studentEntryStream(line);
      std::string token;
         
      std::getline(studentEntryStream, token, ',');
      student.setID(std::stoi(token));
         
      std::getline(studentEntryStream, token, ',');
      student.setLastName(token);
         
      std::getline(studentEntryStream, token, ',');
      student.setFirstName(token);
         
      // There is a variable amount of courses regsitered, so use a while loop
      // to parse each one
      while(std::getline(studentEntryStream, token, ','))
      {
         CourseName courseName = toCourseName(token);

         std::getline(studentEntryStream, token, ',');
         std::string lastName = token;

         std::getline(studentEntryStream, token, ',');
         std::string firstName = token;

         std::string fullName = lastName + "," + firstName;
         ProfessorName professorName = toProfessorName(fullName);

         std::getline(studentEntryStream, token, ',');
         bool alreadyRated = (token == "true");

         // Once each course is fully parsed, create StudentCourseData objects for
         // them and call the student's loadCourse function so they can be stored.
         student.loadCourse(StudentCourseData(courseName, professorName, alreadyRated));
      }
         
      // Once all the data is fully parsed and added to the newly created student,
      // add an entry for that student into studentTable, using their id as the key.
      studentTable.addEntry(StudentEntry(student.getID(), student));

      // Output the added student entry
      student.display();
   }

   fin.close();
}

void Controller::loadCourses()
{
   // Use the File enum to get the correct file name for course data.
   std::ifstream fin(toString(File::courseData).c_str());
   std::string line;

   // Go through each line in the file to get each courses name and list of
   // professors that are teaching the course.
   while (std::getline(fin, line))
   {
      // Use stringstream to parse course's attributes
      std::stringstream courseEntryStream(line);
      std::string token;

      // CourseName is a enum class used to ensure the course names in the file
      // are valid.
      std::getline(courseEntryStream, token, ',');
      CourseName courseName = toCourseName(token);

      std::vector<ProfessorName> professors;

      // There is a variable amount of professors teaching, so use a while loop
      // to parse each one.
      while (std::getline(courseEntryStream, token, ','))
      {
         std::string lastName = token;

         std::getline(courseEntryStream, token, ',');
         std::string firstName = token;

         // There is a ProfessorName enum class used to ensure professor names
         // in the file are accurate. The toProfessorName gets the enum representation
         // of the string in the file.
         std::string fullName = lastName + "," + firstName;

         professors.push_back(toProfessorName(fullName));
      }
      
      // Create an entry for the course and its professors and add it to courseTable
      courseTable.addEntry(courseName, professors);
   }
}

void Controller::loadProfessorTable()
{
   // Use the File enum to get the correct file name for professor data.
   std::ifstream fin(toString(File::professorRatings).c_str());
   std::string line;

   // Go through each line in the file to get each professor's first and last
   // names and their rating, which is represented as total points and number
   // of submissions.
   while(std::getline(fin, line))
   {
      std::stringstream professorEntryStream(line);
      std::string token;

      std::getline(professorEntryStream, token, ',');
      std::string lastName = token;

      std::getline(professorEntryStream, token, ',');
      std::string firstName = token;

      std::getline(professorEntryStream, token, ',');
      int totalPoints = std::stoi(token);

      std::getline(professorEntryStream, token, ',');
      int numSubmissions = std::stoi(token);

      // Use the parsed attributes to create the full name and map it onto the
      // appropriate ProfessorName enum using the toProfessorName() converter.
      // Then, create a Professor object using the result and the rating attributes
      std::string fullName = lastName + "," + firstName;
      ProfessorName professorName = toProfessorName(fullName);
      Professor professor = Professor(professorName, totalPoints, numSubmissions);

      // Add an entry for the new professor to professorTable. NOTE: the professor's
      // enum representation will be used as the key.
      professorTable.addEntry(ProfessorEntry(professor));

      // There is a data member used to keep track of all available professors
      // in a vector, so we don't need to iterate an entire map to get all 
      // professors later on.
      professorTable.addProfessorName(professorName);
   }
}

void Controller::addCoursesToProfessorTable()
{
   std::cout << "Loading course entries from file into CourseTable and "
      << "ProfessorTable objects...\n\n";

   // Use courseTable, which containing a mapping of courses to the professors
   // that are teaching them, to add the appropriate courses to each professor
   // in professorTable.
   for (const auto& [course, professors] : courseTable.getEntries())
   {
      for (const auto& professor : professors)
      {
         Professor* profPtr = professorTable.getProfessor(professor);
         profPtr->addCourse(course);

         // Output what professor-course pairs are being added
         std::cout << "\tCourse " << toString(course) << " added to Professor "
            << profPtr->getFirstName() + " " + profPtr->getLastName()
            << "\'s course list.\n";
      }
   }
}

void Controller::processLandingPage()
{
   LandingPage landingPage;
   landingPage.display();

   // Page objects are responsible for getting and validating user input. The
   // calling function in Controller does additional validation in some cases.
   int optionChoice = landingPage.getOptionChoice();

   // Each possible option is well defined and conditional control can be
   // accomplished with a switch statement.
   switch(optionChoice)
   {
      case 1: 
         processLoginPage();
         break;

      case 2:
         processRegisterAccountPage();
         break;

      case 3:
         std::exit(EXIT_SUCCESS);
         break;

      default:
         std::cout << "Option choice mismatch between page and controller\n\n";
   }
}

void Controller::processLoginPage()
{
   // When creating a loginPage, the pointer to studentTable is supplied so
   // the page can check if a user is registered.
   LoginPage loginPage(&studentTable);
   loginPage.display();

   // LoginPage is responsible for getting checking if the user's id matches
   // a student entry in student table. If theres a match, a pointer to that
   // student object is returned and assigned to the user data member.
   user = loginPage.getStudent();
   
   // If the user input "cancel", the program goes back to the landing page.
   if (user == nullptr)
      processLandingPage();
   else
      processMainMenuPage();
}

void Controller::processRegisterAccountPage()
{
   // When creating a registerAccountPage, the pointer to studentTable is supplied so
   // the page can check if a user is already registered.
   RegisterAccountPage registerAccountPage(&studentTable);
   registerAccountPage.display();
   
   // RegisterAccountPage is responsible for getting the input necessary to register a new
   // student and create a new student object.
   Student student = registerAccountPage.getStudent();
   //
   // If the user input "cancel", the program goes back to the landing page.
   if(student.getID() != -1)
   {
      // Create an entry for the new student and add it to studentTable. Then,
      // get a pointer to the student object in the table and assign it to user.
      // Finally, overwrite the student data file with the new updated studentTable.
      studentTable.addEntry(StudentEntry(student.getID(), student));
      user = studentTable.getStudent(student.getID());
      studentTable.saveToFile(toString(File::studentData));

      processMainMenuPage();
   }
   else
   {
      processLandingPage();
   }
}

void Controller::processMainMenuPage()
{
   MainMenuPage mainMenuPage(user);
   mainMenuPage.display();

   // Page objects are responsible for getting and validating user input. The
   // calling function in Controller does additional validation in some cases.
   int optionChoice = mainMenuPage.getOptionChoice();

   // Each possible option is well defined and conditional control can be
   // accomplished with a switch statement.
   switch(optionChoice)
   {
      case 1: 
         processCourseSelectionPage();
         break;

      case 2:
         processProfessorLookupPage();
         break;

      case 3:
         processCourseLookupPage();
         break;

      case 4:
         processStudentInfoPage();
         break;

      case 5:
         processRateProfessorPage();
         break;

      case 6:
         std::exit(EXIT_SUCCESS);

      default:
         std::cerr << "Option choice mismatch between page and controller\n\n";
         std::exit(EXIT_FAILURE);
   }
}

void Controller::processCourseSelectionPage()
{
   // This page is used to display the courses available for regsitration.
   // The user pointer and a pointer to courseTable are supplied so the page
   // can load the correct data.
   CourseSelectionPage courseSelectionPage(user, &courseTable);
   courseSelectionPage.display();

   // Get and validate the option choice, then determine which course maps to
   // that chocie.
   int optionChoice = courseSelectionPage.getOptionChoice();
   CourseName course = courseTable.getEntries()[optionChoice - 1].first;

   // Next, the list of professors that are teaching the selected course will be
   // shown for the user to choose from. 
   processRegisterProfessorSelectPage(course);
}

void Controller::processRegisterProfessorSelectPage(CourseName targetCourse)
{
   // Create a vector of pointers to professors in professorTable that are
   // teaching the course.
   std::vector<Professor*> professors;
   const std::pair<CourseName, std::vector<ProfessorName>>* entryPtr;
   const std::vector<std::pair<CourseName, std::vector<ProfessorName>>>& table =
      courseTable.getEntries();

   // For each entry in professorTable, determine if the professor is teaching
   // the chosen course, and if so, add a pointer to that professor to the
   // vector.
   for (const auto& entry : table)
   {
      if (entry.first  == targetCourse)
      {
         entryPtr = &entry;
         for (const auto& professorName : entry.second)
         {
            // Hashing is used to search the table using the ProfessorName
            // enum as the key.
            professors.push_back(professorTable.getProfessor(professorName));
         }

         break;
      }
   }

   // Load the professor selection page with parameters that are needed to
   // display the correct data.
   RegisterProfessorSelectPage registerProfessorSelectPage(user, targetCourse, professors);
   registerProfessorSelectPage.display();

   int optionChoice = registerProfessorSelectPage.getOptionChoice();

   // Map the option choice to the corresponding ProfessorName enum, which is used
   // to add a new course to the user list of courses. Since user is a pointer,
   // the studentTable is also updated with the new student's course, and the
   // updated table is saved to file.
   ProfessorName professorName = entryPtr->second[optionChoice - 1];
   user->loadCourse(StudentCourseData(targetCourse, professorName, false));
   studentTable.saveToFile(toString(File::studentData));

   // Getting the professor info to display as part of a message.
   const Professor* professor = professorTable.getProfessor(professorName);
   std::string profDescription = "Professor " + professor->getLastName();

   std::string successMessage = toString(Message::registerSuccess);
   std::string courseInfo = toString(targetCourse) + " with " +
      profDescription;

   // Display a message to the user indicating their registration was successful.
   registerProfessorSelectPage.displayWithoutBody();
   registerProfessorSelectPage.displaySuccess(successMessage, courseInfo);
   registerProfessorSelectPage.pauseWithMessage(toString(Message::returnToMainMenu));

   // Go back to main page.
   processMainMenuPage();
}

void Controller::processProfessorLookupPage()
{
   // This page is used to display a list of all professors that the user can
   // select from to see that professor's courses and rating.
   ProfessorLookupPage professorLookupPage(user, &professorTable);
   professorLookupPage.display();

   int optionChoice = professorLookupPage.getOptionChoice();

   // Map the option choice to the corresponding entry in professorTable
   ProfessorName professorChoice =
      professorTable.getProfessorNames()[optionChoice - 1];

   Professor* professor = professorTable.getProfessor(professorChoice);

   // This will load the chosen professor's info in a new page.
   processProfessorInfoPage(professor);
}

void Controller::processProfessorInfoPage(Professor* professorPtr)
{
   // Display the provided professor's courses and rating.
   ProfessorInfoPage professorInfoPage(user, professorPtr);
   professorInfoPage.display();

   // Go back to main page.
   processMainMenuPage();
}

void Controller::processCourseLookupPage()
{
   // This page is used to display a list of available courses. The user selects
   // a course to see which professors are teaching it as well as those professors'
   // ratings.
   CourseLookupPage courseLookupPage(user, &courseTable);
   courseLookupPage.display();

   int optionChoice = courseLookupPage.getOptionChoice();

   // Map the option choice to the corresponding course.
   CourseName courseChoice =
      courseTable.getEntries()[optionChoice - 1].first;

   // Get list of which professors are teaching the selected course.
   std::vector<ProfessorName> professorNames =
      courseTable.getEntries()[optionChoice - 1].second;

   // Load a new page with the list of professors and their ratings.
   processCourseInfoPage(courseChoice, professorNames);
}

void Controller::processCourseInfoPage(CourseName courseName,
      std::vector<ProfessorName> professorNames)
{
   // Diplay a table the the provided processors and their ratings
   CourseInfoPage courseInfoPage(user, courseName, professorNames, &professorTable);
   courseInfoPage.display();

   // Go back to main page.
   processMainMenuPage();
}

void Controller::processStudentInfoPage()
{
   // Display a table of the user's registered courses, the professors teaching
   // the courses, and whether or not the user has already submitted a rating
   // for those courses.
   StudentInfoPage studentInfoPage(user, &professorTable);
   studentInfoPage.display();

   // Go back to main page.
   processMainMenuPage();
}

void Controller::processRateProfessorPage()
{
   // This page shows a user a table of their registered courses, and gives them
   // the opportunity to submit a rating for one of them. Validatation ensures
   // the user can only submit a rating once for each course.
   RateProfessorPage rateProfessorPage(user, &professorTable);
   rateProfessorPage.display();
   int optionChoice = rateProfessorPage.getOptionChoice();

   // Map the option choice to the corresponding StudentCourseData object.
   StudentCourseData data = user->getCourseDataVector()[optionChoice - 1];

   // Parse out the data into its corresponding CourseName and ProfessorName attributes.
   CourseName courseName = data.course;
   ProfessorName professorName = data.professor;

   // Use the ProfessorName attribute as the key to retrieve a pointer to the
   // corresponding professor in professorTable (hash map).
   Professor* professor = professorTable.getProfessor(professorName);

   std::string profDescription = "Professor " + professor->getLastName();
   int rating = rateProfessorPage.getRating(profDescription);

   // Use the professor pointer to update the professor's rating with the user's
   // newly submitting rating. Then, save the updated professorTable to file.
   professor->addNewRating(rating);
   professorTable.saveToFile(toString(File::professorRatings));

   // After the user submits the rating, the bool attribute tracking whether the
   // course has been rated or not has to be updated. The studentTable is also
   // updated and written to file.
   user->submitRatingForIndex(optionChoice - 1);
   studentTable.saveToFile(toString(File::studentData));

   // Display a message indicating the rating submission was successful.
   std::string successMessage = toString(Message::ratingSuccess);
   std::string courseInfo = toString(courseName) + " with Professor " +
      professor->getLastName();

   // The page is displayed again so the rating submitted bool, for the chosen
   // course is changed from "No" to "Yes" on screen.
   rateProfessorPage.display();
   rateProfessorPage.displaySuccess(successMessage, courseInfo);
   rateProfessorPage.pauseWithMessage(toString(Message::returnToMainMenu));

   // Go back to main page.
   processMainMenuPage();
}




