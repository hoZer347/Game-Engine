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
struct Cell : public MeshObj {
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
	std::function<void(Vtx&)> f;
};

static Grid* create_grid(Renderer* renderer, unsigned int x=10, unsigned int y=10, std::function<void(Vtx&)> f={}, bool animate=false) {
	Grid* g = new Grid();
	g->r = renderer;
	g->f = f;
	g->m = create_square();
	change_rendering(g->m, GL_LINES);

	for (auto& v : g->m->vtxs)
		v.clr = vec4(1, 0, 0, 1);

	OBJS.push_back((MeshObj*)g);

	for (unsigned int i = 0; i < x; i++) {
		g->c.push_back({});
		for (unsigned int j = 0; j < y; j++) {
			Cell* c = new Cell();
			c->animate = animate;
			c->m = create_square();
			for (auto& v : c->m->vtxs) {
				y_is_negz(v);
				v.pos += vec3(i, 0, -(int)j);
			}
			c->g = g;

			change_rendering(c->m, GL_LINES);
			
			OBJS.push_back(c);
			g->c[g->c.size()-1].push_back(c);
		}
	}

	return g;
}
