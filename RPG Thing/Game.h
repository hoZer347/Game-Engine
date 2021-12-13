#pragma once

#include "Room.h"
#include "Timer.h"

class Game {
public:
	Game();
	void init();

	Room* room = NULL;
};

// Does Nothing
static auto null = [](Room*){
	
};
