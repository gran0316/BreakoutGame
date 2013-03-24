#include "SplashScreen.h"
#include "../Game/Game.h"


SplashScreen::SplashScreen() : Menu()
{
    //Add the menu title
    addMenuTitle(new OpenGLTexture(SPLASH_SCREEN_MENU_TITLE));
    
    //Add the menu's background image.
    addMenuBackground(new OpenGLTexture(GAME_BACKGROUND_TEXTURE));
    
    //Add menu option
    addMenuOption(new OpenGLTexture(MENU_OPTION_PRESS_PLAY));
}

SplashScreen::~SplashScreen()
{
    //Everything get destroyed in the Menu class
}

const char* SplashScreen::getName()
{
    return SPLASH_SCREEN_NAME;
}

void SplashScreen::menuAction(int aIndex)
{

}

void SplashScreen::keyUpEvent(int aKeyCode)
{
    if(aKeyCode == KEYCODE_SPACE)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_NAME);
    }
}