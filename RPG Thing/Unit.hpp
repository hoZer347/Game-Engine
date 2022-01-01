#pragma once

#include "Unit.h"

#include "UnitMenu.h"
#include "Menu.h"
#include "Grid.hpp"
#include "Animations.hpp"
#include "Renderer.h"
#include "Inputs.h"
#include "Sound.h"

namespace UnitOptions {
	static void attack(Unit*);
	static void equip(Unit*);
	static void item(Unit*);
	static void end(Unit*);
	static void wait(Unit*);
	static void cancel(Unit*);

	static UnitMenu* get_options(Unit* u) {
		auto unit_menu = create_unit_menu(u);

		unit_menu->add("Cancel", cancel);

		return unit_menu;
	}

	static void attack(Unit* u) {
		// TODO:
	};

	static void equip(Unit* u) {
		// TODO:
	};

	static void item(Unit* u) {
		// TODO:
	};

	static void end(Unit* u) {
		// TODO:
	};

	static void wait(Unit* u) {
		// TODO:
	};

	static void cancel(Unit* u) {
		// TODO:
		std::cout << "Test" << std::endl;
	};
}