#include "Grid.h"

void Cell::update() {
	if (u && u->s)
		u->s->m->trns = translate(m->trns, vec3(0, 0, -.5));
}

void Grid::update() {
	mat3 mat = r->get_cam_ray();

	if (hovered)
		hovered->change_team(hovered->team);

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

	animate = false;
}
