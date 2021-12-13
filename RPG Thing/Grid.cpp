#include "Grid.h"

void Cell::update() {
	vec3 avg = vec3(0);

	for (auto& i : m->vtxs) {
		g->f(i);
		avg += i.pos;
	}

	avg /= m->vtxs.size();

	if (u && u->s && u->s->m)
		u->s->m->trns = translate(mat4(1), avg -= vec3(.5, 0, 0));
}

void Grid::update() {
	mat3 mat = get(r);

	for (auto& i : c) {
		for (auto& j : i) {
			vec3 v;
			if (intersectRayTriangle(mat[0], -mat[1]*=100, j->m->vtxs[0].pos, j->m->vtxs[1].pos, j->m->vtxs[2].pos, v) ||
				intersectRayTriangle(mat[0], -mat[1]*=100, j->m->vtxs[0].pos, j->m->vtxs[2].pos, j->m->vtxs[3].pos, v)) {
				hovered = j;
				m->vtxs = j->m->vtxs;
				m->inds = j->m->inds;
				for (auto& v : m->vtxs) {
					v.clr = vec4(1, 0, 0, 1);
					v.pos += vec3(0, 0.03, 0);
				}
				return;
			}
		}
	}

	m->vtxs.clear();
	m->inds.clear();
	hovered = NULL;
}
