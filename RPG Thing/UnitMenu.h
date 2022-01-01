#pragma once

#include "Menu.h"
#include "Unit.h"
#include "Text.h"
#include "Inputs.h"
#include "Renderer.h"

struct Text;
struct Font;

class UnitOption : public Menu<Unit*>::Option {
public:
	friend class UnitMenu;

	void on();
	void off();
	bool intersect();

protected:
	bool on_off = false;
	Text* t = NULL;
};

class UnitMenu : public Menu<Unit*>{
public:
	void add(const char*, std::function<void(Unit*)>);
	void unload();

	Font* font = NULL;

private:
	Unit* u = NULL;
};

static UnitMenu* create_unit_menu(Unit* u) {
	UnitMenu* m = new UnitMenu();
	m->set(u);
	m->font = create_font();
	m->font->ortho = true;

	OBJS.push_back(m);
	inputs->mem["Menu"] = m;
	
	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int b, int a) {
		UnitMenu* m = (UnitMenu*)inputs->mem["Menu"];

		m->select();
	};

	return m;
}
