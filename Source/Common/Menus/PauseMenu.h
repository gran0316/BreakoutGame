#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Menu.h"

//Pause Menu, inherits from the Menu class, contains three (3) 
//menu options; resume, restart, and quit.
class PauseMenu : public Menu
{
public:
  PauseMenu();
  ~PauseMenu();
 
  //Screen name, must be implemented, it's a pure virtual 
  //method in the Screen class
  const char* getName();

  //Pure Virtual function, inherited from the Menu class, 
  //called when a menu option is selected
  void menuAction(int index);
};

#endif