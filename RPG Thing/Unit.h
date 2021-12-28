#pragma once

#include <string>
#include <vector>

enum U {
	Null = 0,
	RNG = 1,
	ARG = 2
};

class Sprite;

struct Stats {
	unsigned char RNG = 0;
	unsigned char ARG = 0;
};

class Unit {
public:
	Sprite* s = NULL;
	Stats bonus =	{  0,  1 };
	Stats base =	{  5,  0 };
	Stats cap =		{ 12,  5 };

	unsigned char get(unsigned char i) {
		switch (i) {
		case U::RNG:
			return base.RNG + bonus.RNG;
		case U::ARG:
			return base.ARG + bonus.ARG;
		default:
			return NULL;
			break;
		}
	}

	unsigned char team = 1;
	unsigned char skills[5] = { };
};

extern std::vector<Unit*> UNIT;

static Unit* create_unit() {
	Unit* u = new Unit();

	UNIT.push_back(u);

	return u;
}
