#include "LevelSelectMenu.h"
#include "../Game/Game.h"


LevelSelectMenu::LevelSelectMenu() : Menu()
{
    //Add the menu title
    addMenuTitle(new OpenGLTexture(LEVEL_MENU_TITLE));
    
    //Add the menu's background image.
    addMenuBackground(new OpenGLTexture(GAME_BACKGROUND_TEXTURE));
    
    //Add the menu options
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION_1));
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION_2));
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION_3));
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION_4));
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION_5));
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION_6));
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION_7));
    addMenuOption(new OpenGLTexture(MENU_LEVEL_OPTION_8));
    addMenuOption(new OpenGLTexture(MENU_OPTION_BACK));
}

LevelSelectMenu::~LevelSelectMenu()
{
    //Everything get destroyed in the Menu class
}

const char* LevelSelectMenu::getName()
{
    return LEVEL_MENU_NAME;
}

void LevelSelectMenu::menuAction(int aIndex)
{
    Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
    
    if(aIndex == 0)
    {
		game->setLevel(GAME_DEFAULT_LEVEL);
    }
    else if(aIndex == 1)
    {
        game->setLevel(GAME_LEVEL_2);
    }
    else if(aIndex == 2)
    {
        game->setLevel(GAME_LEVEL_3);
    }
    else if(aIndex == 3)
    {
        game->setLevel(GAME_LEVEL_4);
    }
    else if(aIndex == 4)
    {
        game->setLevel(GAME_LEVEL_5);
    }
    else if(aIndex == 5)
    {
        game->setLevel(GAME_LEVEL_6);
    }
    else if(aIndex == 6)
    {
       game->setLevel(GAME_LEVEL_7);
    }
    else if(aIndex == 7)
    {
        game->setLevel(GAME_MAX_LEVEL);
    }
    else if(aIndex == 8)
    {
        ScreenManager::getInstance()->switchScreen(OPTIONS_MENU_NAME);
    }
    
    game->loadGameLevel();
    game->reset();
}