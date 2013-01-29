#ifndef GAME_OVER_MENU_H
#define GAME_OVER_MENU_H

#include "Menu.h"

class GameOverMenu : public Menu
{
public:
	GameOverMenu();
	~GameOverMenu();

	const char* getName();

	void menuAction(int index);
};

#endif