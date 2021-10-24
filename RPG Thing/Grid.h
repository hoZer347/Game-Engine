#pragma once

#include "Container.h"
#include "Renderable.h"

enum {
	U = 0,
	D = 1,
	L = 2,
	R = 3
};

struct Unit {};
struct Terrain {};

struct CellData : Object {
	Unit* u;
	Terrain* t;
};

class Cell : public Place {
public:
	Cell(int X=0, int Y=0) { x = X, y = Y; };

	Cell* operator[](int i);

	Renderable *i=NULL;
	Cell *_u=NULL, *_d=NULL, *_l=NULL, *_r=NULL;
	CellData* d=NULL;
	int x=0, y=0;
};

class Grid : public Container {
public:
	Grid(int=32, int=32);
	
	operator Renderable*() const { return index; };
	operator std::vector<std::vector<Cell*>>& () { return grid; };

	auto& operator[](size_t i) { if (i < grid.size()) return grid[i]; }

private:
	Renderable* index=NULL;
	std::vector<std::vector<Cell*>> grid;
};

