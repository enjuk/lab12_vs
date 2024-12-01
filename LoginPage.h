#ifndef LOGIN_PAGE_H_
#define LOGIN_PAGE_H_

#include "Page.h"
#include "StudentTable.h"

class LoginPage : public Page {
public:
   LoginPage();
   LoginPage(StudentTable* studentMapPtr);
   void display() override;
   Student* getStudent() const;

private:
   std::string pageDescription = "Login for existing user";
   StudentTable* studentMapPtr;

   Student* getUserPtr() const override {return userPtr;}
   std::string getPageDescription() const override {return pageDescription;}

   bool isInSystem(int targetID);
};

#endif
