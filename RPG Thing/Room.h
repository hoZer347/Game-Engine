#pragma once

#include "Renderer.h"
#include "Inputs.h"
#include "Container.h"

struct Room {
	Container* c = NULL;
	Renderer* r = NULL;
	Inputs* i = NULL;
};

static Room* create_room(Container* c, Renderer* r=NULL, Inputs* i=NULL) {
	Room* room = new Room();

	room->c;
	if (!r) room->r = new Renderer();
	else room->r = r;
	if (!i) room->i = new Inputs(room->r->window, room);
	else room->i = i;

	return room;
};

static void destroy_room(Room* r) {
	// TODO:
};
