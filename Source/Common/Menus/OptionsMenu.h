#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "Menu.h"

//Option Menu, inherits from the Menu class, contains four (4)
//menu options; play, options, credits and quit.
class OptionsMenu : public Menu
{
public:
    OptionsMenu();
    ~OptionsMenu();
    
    //Screen name, must be implemented, it's a pure virtual
    //method in the Screen class
    const char* getName();
    
    //Pure Virtual function, inherited from the Menu class,
    //called when a menu option is selected
    void menuAction(int index);
};

#endif