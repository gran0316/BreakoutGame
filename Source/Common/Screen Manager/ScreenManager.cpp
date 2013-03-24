#include "ScreenManager.h"
#include "Screen.h"
#include "../Game/Game.h"
#include "../Menus/PauseMenu.h"
#include "../Menus/GameOverMenu.h"
#include "../Menus/SplashScreen.h"
#include "../Menus/MainMenu.h"
#include "../Menus/OptionsMenu.h"
#include "../Menus/CreditsMenu.h"
#include "../Menus/WinMenu.h"
#include "../Menus/LevelSelectMenu.h"
#include "../Menus/CreditsMenu.h"

#include <time.h>

ScreenManager* ScreenManager::m_Instance = NULL;
ScreenManager* ScreenManager::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new ScreenManager();
	}
	
	return m_Instance;
}

void ScreenManager::cleanupInstance()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

ScreenManager::ScreenManager()
{
  //Seed the rand() function
  srand(time(NULL));
  
  //Initialize member variables
	m_CurrentScreen = NULL;
	m_ScreensLoaded = false;
}

ScreenManager::~ScreenManager()
{
	//delete all of the screens in the manager
	for(unsigned int i = 0; i < m_Screens.size(); i++)
	{
		delete m_Screens.at(i);
	}
	m_Screens.clear();
}

void ScreenManager::loadScreens()
{
	//Create the Game and add it
    addScreen(new SplashScreen());
	addScreen(new Game());
	addScreen(new PauseMenu());
	addScreen(new GameOverMenu());
    addScreen(new MainMenu());
    addScreen(new OptionsMenu());
    addScreen(new CreditsMenu());
    addScreen(new WinMenu());
    addScreen(new LevelSelectMenu());
    addScreen(new CreditsMenu());
}

void ScreenManager::setScreenSize(float aWidth, float aHeight)
{
  m_ScreenWidth = aWidth;
  m_ScreenHeight = aHeight;

  if(m_ScreensLoaded == false)
  {
	loadScreens();
	m_ScreensLoaded = true;
  }
}

float ScreenManager::getScreenWidth()
{
  return m_ScreenWidth;
}

float ScreenManager::getScreenHeight()
{
  return m_ScreenHeight;
}

void ScreenManager::update(double delta)
{
	if(m_CurrentScreen != NULL)
	{
		m_CurrentScreen->update(delta);
	}
}

void ScreenManager::paint()
{
	if(m_CurrentScreen != NULL)
	{
		m_CurrentScreen->paint();
	}
}

void ScreenManager::addScreen(Screen* aScreen)
{
  if(aScreen != NULL)
  {
    //If this is the first screen, make it the current screen
  	if(m_Screens.size() == 0)
    {
      m_CurrentScreen = aScreen;
      m_CurrentScreen->screenWillAppear();
	  InputManager::getInstance()->registerListener(m_CurrentScreen);
    }
  
    //
	m_Screens.push_back(aScreen);
  }
}
	
void ScreenManager::switchScreen(Screen* aScreen)
{
	if(aScreen != NULL)
	{
		switchScreen(aScreen->getName());
	}
}

void ScreenManager::switchScreen(const char* aName)
{
	//look for then screen with the name and make it the current
	for(unsigned int i = 0; i < m_Screens.size(); i++)
	{
		if(strcmp(m_Screens[i]->getName(), aName) == 0)
		{
		  InputManager::getInstance()->unregisterListener();
          m_CurrentScreen->screenWillDisappear();
		  m_CurrentScreen = m_Screens.at(i);
		  m_CurrentScreen->screenWillAppear();
		  InputManager::getInstance()->registerListener(m_CurrentScreen);
		  return;
		}
	}
}

Screen* ScreenManager::getCurrentScreen()
{
	return m_CurrentScreen;
}

Screen* ScreenManager::getScreenForName(const char* aName)
{
	//find the screen and return it
	for(unsigned int i = 0; i < m_Screens.size(); i++)
	{
		if(strcmp(m_Screens.at(i)->getName(), aName) == 0)
		{
			return m_Screens.at(i);
		}
	}
  return NULL;
}
