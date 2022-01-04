#include "Grid.h"

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
				c->u->s->m->trns = r->c->yaww;
				c->u->s->m->trns *= trns;
			}

	// THIS MUST BE THE LAST THING THIS FUNCTION DOES
	for (auto& i : C) {
		for (auto& j : i) {
			vec3 v;
			if (intersectRayTriangle(mat[0], -mat[1]*=100, j->pos(0), j->pos(1), j->pos(2), v) ||
				intersectRayTriangle(mat[0], -mat[1]*=100, j->pos(0), j->pos(2), j->pos(3), v)) {
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

bool Grid::set(Unit* u, unsigned int x, unsigned int y) {
	if (!check_rng(x, y))
		return false;
	
	if (C[x][y] && !C[x][y]->u) {
		C[x][y]->u = new Unit(*u);
		u->c = C[x][y];
	} else
		return false;

	return true;
}

bool Grid::check_rng(unsigned int x, unsigned int y) {
	if (x >= 0 && x < C.size())
		return true;

	if (y >= 0 && C.size() > 0 && y < C[0].size())
		return true;

	return false;
}
