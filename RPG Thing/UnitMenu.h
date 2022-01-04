#pragma once

#include "Menu.h"
#include "Unit.h"
#include "Text.h"
#include "Inputs.h"
#include "Renderer.h"

class Text;
class Font;

class UnitOption : public Menu<Unit>::Option {
public:
	friend class UnitMenu;

	void on();
	void off();
	bool intersect();

protected:
	bool on_off = false;
	Text* t = NULL;
};

class UnitMenu : public Menu<Unit> {
public:
	void del() {
		for (auto& o : O)
			delete o;

		delete this;
	}
	void add(const char*, std::function<void(Unit*)>);
	void unload();

	Font* font = create_font();

private:
	Unit* u = NULL;
};

static UnitMenu* create_unit_menu(Unit* u) {
	UnitMenu* m = new UnitMenu();
	m->set(u);

	inputs->mem["Menu"] = m;
	
	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int b, int a) {
		UnitMenu* m = (UnitMenu*)inputs->mem["Menu"];

		m->select();
	};

	make_meshobj(m);

	return m;
}
