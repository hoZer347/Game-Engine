#pragma once

#include <glm/gtx/intersect.hpp>
#include "Unit.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Timer.h"

#include <set>

enum {
	U = 0,
	D = 1,
	L = 2,
	R = 3
};

enum {
	TEAM_NULL = 0,
	TEAM_R = 1,
	TEAM_G = 2,
	TEAM_B = 3
};

class Grid;
class Unit;

static double G_BUFFER = .1;
static double G_OPACITY = .3;

// Stores units, and other stuff needed in a map
// Knows neighbours, parent grid
class Cell : public MeshObj {
public:
	~Cell() {
		if (u) delete u;
	}
	void update();
	Cell*& operator[] (unsigned int i) { return next[i]; }
	void change_team(unsigned char i) {
		team = i;
		for (auto& v : m->vtxs)
			switch (i) {
			case TEAM_NULL:
				v.clr = vec4(1, 1, 1, G_OPACITY);
				break;
			case TEAM_R:
				v.clr = vec4(1, 0, 0, G_OPACITY);
				break;
			case TEAM_G:
				v.clr = vec4(0, 1, 0, G_OPACITY);
				break;
			case TEAM_B:
				v.clr = vec4(0, 0, 1, G_OPACITY);
				break;
			default:
				break;
			}
	}

	Cell* next[4] = { };
	Unit* u = NULL;

	unsigned char team = 0;
	double terrain = 1;
};

// 2D array of Cells
class Grid : public MeshObj {
public:
	void update();

	Cell* hovered = NULL;
	Cell* selected = NULL;
	Renderer* r = NULL;
	int index = 0;

	std::vector<std::vector<Cell*>> C;
};

auto y_is_negz = [](Vtx& v) {
	float z = v.pos.z;
	float y = v.pos.y;

	v.pos.y = -z;
	v.pos.z = -y;

	return;
};

// Creates a (x, y) - size grid
// f is the function that represents the positions of each cell and their vertices
// animate is whether or not to update each cell
static Grid* create_grid(
	Renderer* renderer,
	unsigned int x=10,
	unsigned int y=10,
	bool animate=false) {
	Grid* g = new Grid();
	g->r = renderer;
	g->m = create_square();
	change_rendering(g->m, GL_LINES);

	OBJS.push_back((MeshObj*)g);

	for (unsigned int i = 0; i < x; i++) {
		g->C.push_back({});
		for (unsigned int j = 0; j < y; j++) {
			Cell* c = new Cell();
			c->m = create_square();
			for (auto& v : c->m->vtxs)
				y_is_negz(v);

			c->m->trns *= 1 - G_BUFFER;
			c->m->trns = translate(mat4(1),
				vec3((int)i + i*G_BUFFER, 0, -(int)j - j * G_BUFFER));
			
			for (auto& v : c->m->vtxs)
				v.clr = vec4(1, 1, 1, G_OPACITY);

			change_rendering(c->m, GL_LINES);
			
			OBJS.push_back(c);
			g->C[g->C.size()-1].push_back(c);
		}
	}

	return g;
}
