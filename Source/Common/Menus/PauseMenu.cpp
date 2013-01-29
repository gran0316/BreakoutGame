#include "PauseMenu.h"
#include "../Game/Game.h"


PauseMenu::PauseMenu() : Menu()
{
  //Add the menu title
  addMenuTitle(new OpenGLTexture(PAUSE_MENU_TITLE));

  //Add the menu options
  addMenuOption(new OpenGLTexture(MENU_OPTION_RESUME));
  addMenuOption(new OpenGLTexture(MENU_OPTION_RESTART));
  addMenuOption(new OpenGLTexture(MENU_OPTION_QUIT));
}

PauseMenu::~PauseMenu()
{
  //Everything get destroyed in the Menu class
}
 
const char* PauseMenu::getName()
{
  return PAUSE_MENU_NAME;
}

void PauseMenu::menuAction(int aIndex)
{
  if(aIndex == 0)
  {
    //Switch back to the Game screen
    ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
  }
  else if(aIndex == 1)
  {
    //Get the game from the ScreenManager
    Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);

    //Reset the game
    game->reset();

    //Switch to the game
    ScreenManager::getInstance()->switchScreen(game);
  }
  else if(aIndex == 2)
  {
    //Exit the game
    exit(0);
  }
}