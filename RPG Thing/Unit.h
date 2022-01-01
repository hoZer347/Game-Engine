#pragma once

#include <string>
#include <vector>
#include <functional>

enum U {
	RNG = 0,
	ARG = 1
};

class Sprite;
class Cell;

class Unit {
public:
	unsigned char get(unsigned char i) { return base[i] + bonus[i]; }
	
	Cell* c = NULL;
	Sprite* s = NULL;

	bool
		has_moved = 0;

	unsigned char
		team = 1,
		equipped = 0,
		items[5] = { },
		skills[5] = { },
		bonus[10] = { 0,  1 },
		base[10] = { 5,  0 },
		cap[10] = { 12,  5 };
};

extern std::vector<Unit*> UNIT;

static Unit* create_unit() {
	Unit* u = new Unit();

	UNIT.push_back(u);

	return u;
}
