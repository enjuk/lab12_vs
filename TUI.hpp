#ifndef TUI_HPP_
#define TUI_HPP_

#include <iostream>

namespace tui
{
   enum class ColorFG {
      black, red, green, yellow, blue, magenta, cyan, white, standard
   };

   inline std::string toString(ColorFG color)
   {
      switch(color)
      {
         case ColorFG::black   : return "\033[30m";
         case ColorFG::red     : return "\033[31m";
         case ColorFG::green   : return "\033[32m";
         case ColorFG::yellow  : return "\033[33m";
         case ColorFG::blue    : return "\033[34m";
         case ColorFG::magenta : return "\033[35m";
         case ColorFG::cyan    : return "\033[36m";
         case ColorFG::white   : return "\033[37m";
         case ColorFG::standard: return "\033[39m";
         default               : return "INVALID ENUM MEMBER";
      }

      return "Invalid Enum Member";
   }

   enum class ColorBG {
      black, red, green, yellow, blue, magenta, cyan, white, standard
   };

   inline std::string toString(ColorBG color)
   {
      switch(color)
      {
         case ColorBG::black   : return "\033[40m";
         case ColorBG::red     : return "\033[41m";
         case ColorBG::green   : return "\033[42m";
         case ColorBG::yellow  : return "\033[43m";
         case ColorBG::blue    : return "\033[44m";
         case ColorBG::magenta : return "\033[45m";
         case ColorBG::cyan    : return "\033[46m";
         case ColorBG::white   : return "\033[47m";
         case ColorBG::standard: return "\033[49m";
         default               : return "INVALID ENUM MEMBER";
      }

      return "Invalid Enum Member";
   }

   enum class Mode {
      bold, dim, italic, underline, blinking, inverse, hidden, strikethrough,
      standard, reset
   };

   inline std::string toString(Mode mode)
   {
      switch(mode)
      {
         case Mode::bold         : return "\033[1m";
         case Mode::dim          : return "\033[2m";
         case Mode::italic       : return "\033[3m";
         case Mode::underline    : return "\033[4m";
         case Mode::blinking     : return "\033[5m";
         case Mode::inverse      : return "\033[7m";
         case Mode::hidden       : return "\033[8m";
         case Mode::strikethrough: return "\033[9m";
         case Mode::standard     : return "";
         case Mode::reset        : return "\033[0m";
         default               : return "INVALID ENUM MEMBER";
      }

      return "Invalid Enum Member";
   }

  
   inline void clearScreen()
   {
      // ANSI escape codes used to clear screen
      std::cout << "\033[H\033[2J\033[3J";
   }  // end of clearScreen()
     

   // unix version
   //inline void pauseProgram()
   //{
   //   // This outputs a message to the user, and halts execution until user
   //   // presses a key.
   //   system("read -p \"Press any key to continue . . .\" -n1 -s");
   //}  // end of pauseProgram()
   
   
   // unix version
   //inline void pauseProgramWithMessage(const std::string& message)
   //{
   //   std::string systemCall = "read -p \"" + message + "\" -n1 -s";
   //   // This outputs a message to the user, and halts execution until user
   //   // presses a key.
   //   system(systemCall.c_str());
   //}  // end of pauseProgram()

   // windows version
   inline void pauseProgram()
   {
       std::cout << "  ";
       system("pause");
   }  // end of pauseProgram()

   // windows version
   inline void pauseProgramWithMessage(const std::string& message)
   {
       std::cout << "  ";
       system("pause");
   }  // end of pauseProgram()

   inline void moveCursor(int posX, int posY)
   {
      std::string ansiCode = "\033[" + std::to_string(posY) + ";"
         + std::to_string(posX) + "H";

      std::cout << ansiCode;
   }

   inline void moveCursorUp(int numLines)
   {
      std::string ansiCode = "\033[" + std::to_string(numLines) + "A";
      std::cout << ansiCode;
   }

   inline void moveCursorDown(int numLines)
   {
      std::string ansiCode = "\033[" + std::to_string(numLines) + "B";
      std::cout << ansiCode;
   }

   inline void saveCursorPosition()
   {
      std::cout << "\0337";
   }

   inline void restoreCursorPosition()
   {
      std::cout << "\0338";
   }

   inline void clearLine()
   {
      std::cout << "\033[2K";
   }

   inline void clearLines(int numLines)
   {
      for (int i = 0; i < numLines; ++i)
      {
         clearLine();
         moveCursorDown(1);
      }
   }

   inline std::string customizeStr(const std::string& str, tui::ColorFG colorFG,
         tui::Mode mode = tui::Mode::standard, tui::ColorBG colorBG = tui::ColorBG::standard)
   {
      std::string modifiers = toString(colorFG) + toString(colorBG) + toString(mode);

      return  modifiers + str + toString(Mode::reset);
   }
}


#endif
