#include "FTL.h"

FTL::FTL(Room* r) : Game::Game(r) {
	r->c = new Grid();
}
