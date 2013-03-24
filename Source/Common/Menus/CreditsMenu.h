#ifndef CREDITS_MENU_H
#define CREDITS_MENU_H

#include "Menu.h"

//CreditsMenu, inherits from the Menu class, contains credits.
class CreditsMenu : public Menu
{
public:
    CreditsMenu();
    ~CreditsMenu();
    
    //Screen name, must be implemented, it's a pure virtual
    //method in the Screen class
    const char* getName();
    
    //Update the scrolling screen. 
    void paint();
    
    //Pure Virtual function, inherited from the Menu class,
    //called when a menu option is selected
    void menuAction(int index);
    
    //Key up event.
    void keyUpEvent(int keyCode);
    
private:
    OpenGLTexture* m_BackgroundImage;
};

#endif