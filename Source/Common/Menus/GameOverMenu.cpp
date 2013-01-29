#include "GameOverMenu.h"
#include "../Game/Game.h"

GameOverMenu::GameOverMenu()
{
	addMenuTitle(new OpenGLTexture(GAME_OVER_MENU_TITLE));

	addMenuOption(new OpenGLTexture(MENU_OPTION_PLAY_AGAIN));
	addMenuOption(new OpenGLTexture(MENU_OPTION_QUIT));
}
GameOverMenu::~GameOverMenu()
{

}

const char* GameOverMenu::getName()
{
	return GAME_OVER_MENU_NAME;
}

void GameOverMenu::menuAction(int aIndex)
{
	if(aIndex == 0)
	{
		Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
		game->reset();
		ScreenManager::getInstance()->switchScreen(game);
	}
	else if(aIndex == 1)
	{
		exit(0);
	}
}