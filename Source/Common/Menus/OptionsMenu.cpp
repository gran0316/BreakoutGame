#include "OptionsMenu.h"
#include "../Game/Game.h"


OptionsMenu::OptionsMenu() : Menu()
{
    //Add the menu title
    addMenuTitle(new OpenGLTexture(OPTIONS_MENU_TITLE));
    
    //Add the menu's background image.
    addMenuBackground(new OpenGLTexture(GAME_BACKGROUND_TEXTURE));
    
    //Add the menu options
    addMenuOption(new OpenGLTexture(MENU_INPUT_OPTION_M));
    addMenuOption(new OpenGLTexture(MENU_INPUT_OPTION_K));
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION));
    addMenuOption(new OpenGLTexture(MENU_OPTION_BACK));
}

OptionsMenu::~OptionsMenu()
{
    //Everything get destroyed in the Menu class
}

const char* OptionsMenu::getName()
{
    return OPTIONS_MENU_NAME;
}

void OptionsMenu::menuAction(int aIndex)
{
       Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
    
    if(aIndex == 0 || aIndex == 1)
    {
		game->toggleControl();
    }
    else if(aIndex == 2)
    {
        ScreenManager::getInstance()->switchScreen(LEVEL_MENU_NAME);
    }
    else if(aIndex == 3)
    {
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_NAME);
    }
}