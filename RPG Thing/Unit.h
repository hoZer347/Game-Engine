#pragma once

#include "Mesh.h"
#include "Sprite.h"

#include <string>

struct Stats {

};

struct Unit {
	Sprite* s = NULL;
	Stats bonus;
	Stats base;

	short team = 0;
	short skills[5] = { };
};

static Unit* create_unit() {
	Unit* u = new Unit();
	u->s = create_sprite();
	bind_texture(u->s);

	return u;
}