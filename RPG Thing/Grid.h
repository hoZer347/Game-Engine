#pragma once

#include "Mesh.h"
#include "Timer.h"

enum {
	U = 0,
	D = 1,
	L = 2,
	R = 3
};

struct Cell {
	Cell* next[4] = { };
	Mesh* m = NULL;
	Mesh* o = NULL;
	std::vector<unsigned int> inds;
	std::vector<unsigned int> onds;
};

class Grid : public MeshObj {
public:
	void update() {
		if (animate)
			for (auto& v : m->vtxs)
				f(v);
	};
	bool animate = true;
	std::vector<std::vector<Cell*>> c;
	std::function<void(Vtx&)> f;
};

struct Path {
	std::vector<Cell*> c;
};

static Grid* create_grid(unsigned int x=10, unsigned int y=10, std::function<void(Vtx&)> f={}, bool animate=false) {
	Grid* g = new Grid();
	g->m = create_plane(x, y);
	g->f = f;
	g->animate = animate;

	for (auto& v : g->m->vtxs) {
		y_is_negz(v);
		f(v);
	}

	for (unsigned int i = 0; i < x; i++) {
		g->c.push_back({});

		for (unsigned int j = 0; j < y; j++) {
			Cell* c = new Cell();
			c->m = g->m;
			c->inds.push_back(i + 4 * j + 0);
			c->inds.push_back(i + 4 * j + 1);
			c->inds.push_back(i + 4 * j + 2);
			c->inds.push_back(i + 4 * j + 3);
			g->c[i].push_back(c);
		}
	}

	change_rendering(g->m, GL_LINES);

	OBJS.push_back(g);

	return g;
}

static auto a_sinx_sinz = [](Vtx& v) {
	float d = (float)ticks / 100;
	v.pos.y = (sin(v.pos.x + d) + sin(v.pos.z + d))/4;
	
	return;
};
