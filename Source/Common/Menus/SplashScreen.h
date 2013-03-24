#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include "Menu.h"

//SplashScreen, inherits from the Menu class, contains "Press space to play"
class SplashScreen : public Menu
{
public:
    SplashScreen();
    ~SplashScreen();
    
    //Screen name, must be implemented, it's a pure virtual
    //method in the Screen class
    const char* getName();
    
    //Pure Virtual function, inherited from the Menu class,
    //called when a menu option is selected
    void menuAction(int index);
    
    //Press space to continue.
    void keyUpEvent(int keyCode);
};

#endif