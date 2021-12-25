#include "Grid.h"

void Cell::update() {
	if (u && u->s)
		u->s->m->trns = translate(m->trns, vec3(0, 0, -.5));
}

void Grid::update() {
	mat3 mat = r->get_cam_ray();

	for (auto& i : c) {
		for (auto& j : i) {
			vec3 v;
			if (intersectRayTriangle(mat[0], -mat[1]*=100, j->pos(0), j->pos(1), j->pos(2), v) ||
				intersectRayTriangle(mat[0], -mat[1]*=100, j->pos(0), j->pos(2), j->pos(3), v)) {
				hovered = j;
				m->vtxs = j->m->vtxs;
				m->inds = j->m->inds;
				for (int k = 0; k < m->vtxs.size(); k++) {
					m->vtxs[k].clr = vec4(1, 0, 0, 1);
					m->vtxs[k].pos = j->pos(k) + vec3(0, 0.001, 0);
				}
				return;
			}
		}
	}

	m->vtxs.clear();
	m->inds.clear();
	hovered = NULL;
}
