#pragma once

#include "Animation.h"

#include <string>
#include <vector>
#include <functional>

enum U {
	ANIM_ATK = 0,
	ANIM_DEF = 1,
	RNG = 0,
	ARG = 1
};

class Sprite;

class Unit : public MeshObj<Unit> {
public:
	unsigned char get(unsigned char i) { return base[i] + bonus[i]; }
	void update();
	std::vector<unsigned short>& get_options();
	std::vector<unsigned short>& get_skills();

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
	std::vector<Animation*> animations;
	std::vector<unsigned short> options;
	std::vector<unsigned short> skills;
};

extern Unit* create_unit();
