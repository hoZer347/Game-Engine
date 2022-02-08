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
	std::vector<unsigned short>& get_options();
	std::vector<unsigned short>& get_skills();

	Cell* c = NULL;
	Sprite* s = NULL;

	bool
		has_moved = false;

	unsigned char
		team = 1,
		_skills[5] = { },
		bonus[10] = { 0,  0 },
		base[10] = { 5,  1 },
		cap[10] = { 0,  0 };

private:
	std::vector<unsigned short> options = { };
	std::vector<unsigned short> skills = { };
};

extern std::vector<Unit*> UNIT;

extern Unit* create_unit();
