#pragma once

#include <glm/gtx/intersect.hpp>
#include "Mesh.h"
#include "Renderer.h"
#include "Timer.h"
#include "Unit.h"

enum {
	U = 0,
	D = 1,
	L = 2,
	R = 3
};

class Grid;

// Stores units, and other stuff needed in a map
// Knows neighbours, parent grid
class Cell : public MeshObj {
public:
	void update();

	Cell* next[4] = { };
	Unit* u = NULL;
	Grid* g = NULL;
	unsigned short terrain = 0;
};

// 2D array of Cells
class Grid : public MeshObj {
public:
	void update();

	Cell* hovered = NULL;
	Cell* selected = NULL;
	Renderer* r = NULL;

	std::vector<std::vector<Cell*>> c;
};

// Creates a (x, y) - size grid
// f is the function that represents the positions of each cell and their vertices
// animate is whether or not to update each cell
static Grid* create_grid(Renderer* renderer, unsigned int x=10, unsigned int y=10, bool animate=false) {
	Grid* g = new Grid();
	g->r = renderer;
	g->m = create_square();
	change_rendering(g->m, GL_LINES);

	for (auto& v : g->m->vtxs)
		v.clr = vec4(1, 0, 0, 1);

	OBJS.push_back((MeshObj*)g);

	for (unsigned int i = 0; i < x; i++) {
		g->c.push_back({});
		for (unsigned int j = 0; j < y; j++) {
			Cell* c = new Cell();
			c->m = create_square();
			for (auto& v : c->m->vtxs)
				y_is_negz(v);

			c->m->trns = translate(mat4(1), vec3((int)i, 0, -(int)j));
			
			c->g = g;

			change_rendering(c->m, GL_LINES);
			
			OBJS.push_back(c);
			g->c[g->c.size()-1].push_back(c);
		}
	}

	return g;
}
