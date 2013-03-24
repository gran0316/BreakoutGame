#include "WinMenu.h"
#include "../Game/Game.h"

WinMenu::WinMenu()
{
	addMenuTitle(new OpenGLTexture(WIN_MENU_TITLE));
    addMenuBackground(new OpenGLTexture(GAME_BACKGROUND_TEXTURE));
	addMenuOption(new OpenGLTexture(MENU_OPTION_PLAY_AGAIN));
    addMenuOption(new OpenGLTexture(MENU_OPTION_CREDITS));
	addMenuOption(new OpenGLTexture(MENU_OPTION_QUIT));
}
WinMenu::~WinMenu()
{
    
}

const char* WinMenu::getName()
{
	return WIN_MENU_NAME;
}

void WinMenu::menuAction(int aIndex)
{
	if(aIndex == 0)
	{
		Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
		game->restartGame();
		ScreenManager::getInstance()->switchScreen(game);
	}
	else if(aIndex == 1)
	{
        Menu* credits = (Menu*)ScreenManager::getInstance()->getScreenForName(CREDITS_MENU_NAME);
        
        credits->m_ScrollValue = 0.0f;
        
        ScreenManager::getInstance()->switchScreen(CREDITS_MENU_NAME);
	}
    else if(aIndex == 2)
	{
        ScreenManager::getInstance()->switchScreen(MAIN_MENU_NAME);
	}
}