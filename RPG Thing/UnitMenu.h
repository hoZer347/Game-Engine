#pragma once

#include "Menu.h"

class Text;
class Font;
class Unit;

class UnitOption : public Menu::Option {
public:
	friend class UnitMenu;

	void on();
	void off();
	bool intersect();

protected:
	bool on_off = true;
	Text* t = NULL;
};

class UnitMenu : public Menu {
public:
	void del() {
		for (auto& o : O)
			delete o;

		delete this;
	}
	void unload();
	void change_focus(bool);
	void add(const char*, std::function<void()>);

	Unit* unit = NULL;
	Font* font = NULL;
};

extern void create_unit_menu(std::vector<unsigned short>& options);
