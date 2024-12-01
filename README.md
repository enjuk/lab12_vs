Platform
  - This is meant to be built and ran windows using visual studio.
  - A macOS/linux version using cmake is available here: https://github.com/enjuk/lab12_unix

Build Instructions
  - The repo should have all the visual studio solution files needed to just run the application as is.

Warnings
  - I didn't have time to add the ability to cancel an ongoing action or return to the previous page. The only solution is to kill the program.
  - Professors need to have at least one rating stored in the professor_rating.csv file or the program will crash.
  - There is no validation of the data files, so if they are corrupted from outside the program it will likely crash.
  - Working data files are stored in the _default_files directory. Copy them to the main project directory if you need to replace corrupted files.
