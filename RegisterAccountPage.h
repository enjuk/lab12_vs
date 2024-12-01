#ifndef REGISTER_ACCOUNT_PAGE_H_
#define REGISTER_ACCOUNT_PAGE_H_

#include "StudentTable.h"
#include "Page.h"

class RegisterAccountPage : public Page {
public:
   RegisterAccountPage();
   RegisterAccountPage(StudentTable* studentMapPtr);
   void display() override;

   Student getStudent();
   int getStudentID();
   std::string getFirstName();
   std::string getLastName();

private:
   std::string pageDescription = "Register a new account";
   StudentTable* studentMapPtr;

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}
};

#endif
