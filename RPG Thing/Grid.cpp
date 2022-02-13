#include "Grid.h"

#include <glm/gtx/intersect.hpp>
#include "Mesh.h"
#include "Camera.h"
#include "Sprite.h"
#include "Timer.h"
#include "Inputs.h"
#include "Renderer.h"

#include <vector>

Grid* GRID = NULL;

void create_grid(
	unsigned int x,
	unsigned int y,
	bool animate) {
	GRID = new Grid();
	GRID->m = create_square();
	change_rendering(GRID->m, GL_LINES);

	make_meshobj(GRID);

	for (unsigned int i = 0; i < x; i++) {
		GRID->C.push_back({});
		for (unsigned int j = 0; j < y; j++) {
			Cell* c = new Cell();
			c->m = create_square();
			for (auto& v : c->m->vtxs)
				y_is_negz(v);

			c->m->trns *= 1 - G_BUFFER;
			c->m->trns = translate(mat4(1),
				vec3((int)i + i * G_BUFFER, 0, -(int)j - j * G_BUFFER));

			for (auto& v : c->m->vtxs)
				v.clr = vec4(1, 1, 1, G_OPACITY);

			change_rendering(c->m, GL_LINES);

			make_meshobj(c);

			GRID->C[GRID->C.size() - 1].push_back(c);
		}
	}
}

Cell::~Cell() {
	if (u) delete u;
}

void Cell::update() {
	if (u && u->s)
		u->s->m->trns = translate(m->trns, vec3(0, 0, -.5));
}

void Grid::update() {
	mat2x3& mat = inputs->mouse_ray;

	if (hovered)
		hovered->change_color(hovered->clr);

	for (auto& i : C)
		for (auto& c : i)
			if (c->u && c->u->s) {
				mat4 trns = c->u->s->m->trns;
				c->u->s->m->trns *= inverse(trns);
				c->u->s->m->trns = RENDERER->c->yaww;
				c->u->s->m->trns *= trns;
			}

	// THIS MUST BE THE LAST THING THIS FUNCTION DOES
	for (auto& i : C) {
		for (auto& j : i) {
			vec3 v;
			if (intersectRayTriangle(mat[0], mat[1], j->pos(0), j->pos(1), j->pos(2), v) ||
				intersectRayTriangle(mat[0], mat[1], j->pos(0), j->pos(2), j->pos(3), v)) {
				hovered = j;
				for (auto& vtx : hovered->m->vtxs)
					vtx.clr = vec4(0, 0, 0, G_OPACITY);
				return;
			}
		}
	}

	m->vtxs.clear();
	m->inds.clear();
	hovered = NULL;
	//
}

Unit* Grid::get(unsigned int x, unsigned int y) {
	if (!check_rng(x, y))
		return NULL;

	if (C[x][y])
		return C[x][y]->u;
	else
		return NULL;
}

bool Grid::check_rng(unsigned int x, unsigned int y) {
	if (x >= 0 && x < C.size())
		return true;

	if (y >= 0 && C.size() > 0 && y < C[0].size())
		return true;

	return false;
}

void flood_fill(Cell* o, std::set<Cell*>& C, std::function<double(Cell*, Cell*)> f, double i, Cell* c) {
	if (!c || i <= 0) return;

	i -= f(o, c);

	C.insert(c);

	flood_fill(o, C, f, i, (*c)[U]);
	flood_fill(o, C, f, i, (*c)[D]);
	flood_fill(o, C, f, i, (*c)[L]);
	flood_fill(o, C, f, i, (*c)[R]);
}

void a_star(Cell* goal, Cell* c, std::vector<Cell*>& path, std::map<Cell*, unsigned short> visited) {

}

void grid_attach_neighbours() {
	for (unsigned int i = 0; i < GRID->C.size(); i++)
		for (unsigned int j = 0; j < GRID->C[0].size(); j++) {
			if (j < GRID->C.size() - 1)
				(*GRID->C[i][j])[U] = GRID->C[i][j + 1];
			if (j > 0)
				(*GRID->C[i][j])[D] = GRID->C[i][j - 1];
			if (i > 0)
				(*GRID->C[i][j])[L] = GRID->C[i - 1][j];
			if (i < GRID->C.size() - 1)
				(*GRID->C[i][j])[R] = GRID->C[i + 1][j];
		}
}

extern bool grid_set(Unit* u, unsigned int x, unsigned int y) {
	if (!GRID->check_rng(x, y))
		return false;

	if (GRID->C[x][y] && !GRID->C[x][y]->u) {
		GRID->C[x][y]->u = new Unit(*u);
	}
	else
		return false;

	return true;
}

std::function<double(Cell*, Cell*)> u_ff = [](Cell* o, Cell* c) {
	if (!c || !o || !o->u)
		return 10000000.;

	if (!c->u || c->clr == TEAM_NULL || c->u->team == o->clr)
		return c->terrain;

	return 10000000.;
};
std::function<void(Vtx&)> y_is_negz = [](Vtx& v) {
	float z = v.pos.z;
	float y = v.pos.y;

	v.pos.y = -z;
	v.pos.z = -y;

	return;
};
