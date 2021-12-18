#include "Grid.h"

void Cell::update() {

}

void Grid::update() {
	mat3 mat = r->get_cam_ray();

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
