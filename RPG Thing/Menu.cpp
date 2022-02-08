#include "Menu.h"

Menu* MENU = NULL;

void prev_menu() {
	Menu* m = MENU;

	MENU = MENU->_prev;
	m->_prev = NULL;
	m->unload();

	if (MENU)
		MENU->change_focus(true);

	prev_inputs();
};
