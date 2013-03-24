#ifndef WIN_MENU_H
#define WIN_MENU_H

#include "Menu.h"

class WinMenu : public Menu
{
public:
	WinMenu();
	~WinMenu();
    
	const char* getName();
    
	void menuAction(int index);
};

#endif