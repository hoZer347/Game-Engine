#pragma once

#include "Renderer.h"
#include "Inputs.h"

struct Room {
	Renderer* r = NULL;
	Inputs* i = NULL;
};

static Room* create_room(Renderer* r=NULL, Inputs* i=NULL) {
	Room* room = new Room();

	if (!r) room->r = new Renderer();
	else room->r = r;
	if (!i) room->i = new Inputs(room->r->window, room);
	else room->i = i;

	return room;
};
