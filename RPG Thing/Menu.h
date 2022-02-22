#pragma once

#include "Mesh.h"
#include "Inputs.h"

#include <vector>
#include <functional>

class Menu;

extern Menu* MENU;

// Wrapper for menus
// Allows different types of menus to stack onto each other
class Menu : public MeshObj<Menu> {
public:
	class Option {
	public:
		friend class Menu;

		virtual void on()=0;
		virtual void off()=0;
		virtual bool intersect()=0;

	protected:
		std::function<void()> f;
	};

	void update() {
		hovered = NULL;

		for (auto& o : O)
			if (o->intersect()) {
				hovered = o;
				o->on();
			}
			else
				o->off();
	};

	void select() {
		if (hovered)
			hovered->f();
	};

	virtual void change_focus(bool)=0;
	virtual void unload()=0;
	virtual void add(const char*, std::function<void()>)=0;
	
	Menu *_prev = NULL;

protected:
	Option* hovered = NULL;
	std::vector<Option*> O;
};

template<class T>
// Creates a menu of the given type
// - Keeps the last one
static void new_menu() {
	T* m = new T();
	
	if (MENU) {
		m->_prev = MENU;
		MENU->change_focus(false);
	}

	MENU = m;
	inputs->mem["Menu"] = MENU;

	MENU->change_focus(true);

	new_inputs();
};

// Accesses the previous menu
// - Deletes the menu from which it traverses
static void prev_menu() {
	Menu* m = MENU;

	MENU = MENU->_prev;
	m->_prev = NULL;
	m->unload();
	
	if (MENU)
		MENU->change_focus(true);

	prev_inputs();
};
