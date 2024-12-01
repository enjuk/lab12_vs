// Lab_12
// ============================================================================
//
// Programmer: Chris Lewis
// Class: CS 1D
// Instructor: Med Mogasemi
//
// ============================================================================
// Program: Array Based UnsortedLists (HW_1a)
// ============================================================================
// Description:
// Partial implementation of an unsorted list ADT using a fixed size array.
// User is able to insert items to and deletes items from a list.
// ============================================================================
// ============================================================================

#include "Controller.h"

int main()
{
   // The controller is used to control which page should be active and controls
   // the flow of data to and from the pages. When the controller is instantiated,
   // it loads all student, course, and professor data into data members.
   Controller controller;

   // Tells the controller to first load the landing page. From here, the controller
   // dictates the flow of data and pages for the rest of the program.
   controller.processLandingPage();
}
