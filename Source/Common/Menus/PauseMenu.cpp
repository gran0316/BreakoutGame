#include "PauseMenu.h"
#include "../Game/Game.h"


PauseMenu::PauseMenu() : Menu()
{
  //Add the menu title
  addMenuTitle(new OpenGLTexture(PAUSE_MENU_TITLE));
  
  //Add the menu's background image.
  addMenuBackground(new OpenGLTexture(GAME_BACKGROUND_TEXTURE));

  //Add the menu options
  addMenuOption(new OpenGLTexture(MENU_OPTION_RESUME));
  addMenuOption(new OpenGLTexture(MENU_OPTION_RESTART_LEVEL));
  addMenuOption(new OpenGLTexture(MENU_OPTION_RESTART_GAME));
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
    //Get the game from the ScreenManager
    Game* game = (Game*)ScreenManager::getInstance()->getScreenForName(GAME_SCREEN_NAME);
    
  if(aIndex == 0)
  {
    //Switch back to the Game screen
    ScreenManager::getInstance()->switchScreen(GAME_SCREEN_NAME);
  }
  else if(aIndex == 1)
  {
    //Reset the level.
    game->reset();

    //Switch to the game
    ScreenManager::getInstance()->switchScreen(game);
  }
  else if(aIndex == 2)
  {
    //Restart the game.
    game->restartGame();
      
    //Switch to the game
    ScreenManager::getInstance()->switchScreen(game);
  }
  else if(aIndex == 3)
  {
    //Exit the game
    ScreenManager::getInstance()->switchScreen(MAIN_MENU_NAME);
  }
}