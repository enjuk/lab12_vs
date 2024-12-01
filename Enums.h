#ifndef ENUMS_H_
#define ENUMS_H_

#include <string>
#include <vector>

enum class File {
   studentData, courseData, professorData, professorRatings, INVALID
};

enum class CourseName {
   CS1A, CS1B, CS1C, CS1D, CS3A, CS3B, CS4A, CS4B, CS30A, CS30B, INVALID
};

enum class ProfessorName {
   Nadia_A, Barnett_J, Begalli_D, Bodhanwala_H, Eaton_G, Kath_J,
   Khademzadeh_A, Lebowitz_J, Mogasemi_M, Oliveira_C, Rainey_D, Rousseau_M,
   INVALID
};


inline std::string toString(File fileName)
{
   switch(fileName)
   {
      case File::studentData     : return "student_data_spring_2025.csv";
      case File::courseData      : return "course_data_spring_2025.csv";
      case File::professorData   : return "professor_data_spring_2025.csv";
      case File::professorRatings: return "professor_ratings.csv";
      case File::INVALID         : return "Invalid file name";
      default                    : return "Invalid Enum Member";
   }

   return "Invalid Enum Member";
}

inline std::string toString(CourseName courseName)
{
   switch(courseName)
   {
      case CourseName::CS1A   : return "CS-1A";
      case CourseName::CS1B   : return "CS-1B";
      case CourseName::CS1C   : return "CS-1C";
      case CourseName::CS1D   : return "CS-1D";
      case CourseName::CS3A   : return "CS-3A";
      case CourseName::CS3B   : return "CS-3B";
      case CourseName::CS4A   : return "CS-4A";
      case CourseName::CS4B   : return "CS-4B";
      case CourseName::CS30A  : return "CS-30A";
      case CourseName::CS30B  : return "CS-30B";
      case CourseName::INVALID: return "Invalid course name";
      default                 : return "Invalid Enum Member";
   }

   return "Invalid Enum Member";
}

inline CourseName toCourseName(const std::string& courseName)
{
   if (courseName == toString(CourseName::CS1A))
      return CourseName::CS1A;
   else if (courseName == toString(CourseName::CS1B))
      return CourseName::CS1B;
   else if (courseName == toString(CourseName::CS1C))
      return CourseName::CS1C;
   else if (courseName == toString(CourseName::CS1D))
      return CourseName::CS1D;
   else if (courseName == toString(CourseName::CS3A))
      return CourseName::CS3A;
   else if (courseName == toString(CourseName::CS3B))
      return CourseName::CS3B;
   else if (courseName == toString(CourseName::CS4A))
      return CourseName::CS4A;
   else if (courseName == toString(CourseName::CS4B))
      return CourseName::CS4B;
   else if (courseName == toString(CourseName::CS30A))
      return CourseName::CS30A;
   else if (courseName == toString(CourseName::CS30B))
      return CourseName::CS30B;
   else
      return CourseName::INVALID;
}

inline std::string toString(ProfessorName professor)
{
   switch(professor)
   {
      case ProfessorName::Nadia_A      : return "Ahmed,Nadia";
      case ProfessorName::Barnett_J    : return "Barnett,Jeff";
      case ProfessorName::Begalli_D    : return "Begalli,Domingos";
      case ProfessorName::Bodhanwala_H : return "Bodhanwala,Homi";
      case ProfessorName::Eaton_G      : return "Eaton,George";
      case ProfessorName::Kath_J       : return "Kath,John";
      case ProfessorName::Khademzadeh_A: return "Khademzadeh,Ahmed";
      case ProfessorName::Lebowitz_J   : return "Lebowitz,Jerry";
      case ProfessorName::Mogasemi_M   : return "Mogasemi,Med";
      case ProfessorName::Oliveira_C   : return "Oliveira,Carlos";
      case ProfessorName::Rainey_D     : return "Rainey,Dennis";
      case ProfessorName::Rousseau_M   : return "Rousseau,Michele";
      case ProfessorName::INVALID      : return "Invalid professor name";
   }

   return "Invalid Enum Member";
}

inline ProfessorName toProfessorName(const std::string& professorName)
{
   if (professorName == toString(ProfessorName::Nadia_A))
      return ProfessorName::Nadia_A;
   else if (professorName == toString(ProfessorName::Barnett_J))
      return ProfessorName::Barnett_J;
   else if (professorName == toString(ProfessorName::Begalli_D))
      return ProfessorName::Begalli_D;
   else if (professorName == toString(ProfessorName::Bodhanwala_H))
      return ProfessorName::Bodhanwala_H;
   else if (professorName == toString(ProfessorName::Eaton_G))
      return ProfessorName::Eaton_G;
   else if (professorName == toString(ProfessorName::Kath_J))
      return ProfessorName::Kath_J;
   else if (professorName == toString(ProfessorName::Khademzadeh_A))
      return ProfessorName::Khademzadeh_A;
   else if (professorName == toString(ProfessorName::Lebowitz_J))
      return ProfessorName::Lebowitz_J;
   else if (professorName == toString(ProfessorName::Mogasemi_M))
      return ProfessorName::Mogasemi_M;
   else if (professorName == toString(ProfessorName::Oliveira_C))
      return ProfessorName::Oliveira_C;
   else if (professorName == toString(ProfessorName::Rainey_D))
      return ProfessorName::Rainey_D;
   else if (professorName == toString(ProfessorName::Rousseau_M))
      return ProfessorName::Rousseau_M;
   else
      return ProfessorName::INVALID;
}

#endif
