#include "MainMenu.h"
#include "../Game/Game.h"


MainMenu::MainMenu() : Menu()
{
    //Add the menu title
    addMenuTitle(new OpenGLTexture(MAIN_MENU_TITLE));
    
    //Add the menu's background image.
    addMenuBackground(new OpenGLTexture(GAME_BACKGROUND_TEXTURE));
    
    //Add the menu options
    addMenuOption(new OpenGLTexture(MENU_OPTION_PLAY));
    addMenuOption(new OpenGLTexture(MENU_OPTION_OPTION));
    addMenuOption(new OpenGLTexture(MENU_OPTION_CREDITS));
    addMenuOption(new OpenGLTexture(MENU_OPTION_QUIT));
}

MainMenu::~MainMenu()
{
    //Everything get destroyed in the Menu class
}

const char* MainMenu::getName()
{
    return MAIN_MENU_NAME;
}

void MainMenu::menuAction(int aIndex)
{
    if(aIndex == 0)
    {
        //Get the game from the ScreenManager
        Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
        
        //Reset the game
        game->restartGame();
        
        //Switch to the game
        ScreenManager::getInstance()->switchScreen(game);
    }
    else if(aIndex == 1)
    {
        Menu* credits = (Menu*)ScreenManager::getInstance()->getScreenForName(CREDITS_MENU_NAME);
        
        credits->m_ScrollValue = 0.0f;
        
        ScreenManager::getInstance()->switchScreen(OPTIONS_MENU_NAME);
    }
    else if(aIndex == 2)
    {
       ScreenManager::getInstance()->switchScreen(CREDITS_MENU_NAME);
    }
    else if(aIndex == 3)
    {
        exit(0);
    }
}