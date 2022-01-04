#include "Sprite.h"

void Sprite::update() {
	if (curr_time - last_time >= interval && m->gl_texture) {
		last_time = curr_time;

		bool reset = false;

		for (auto& i : m->vtxs) {
			i.cds.x += x_stride;
			if (i.cds.x > 1) {
				reset = true;
				break;
			}
		}

		if (reset) {
			m->vtxs[0].cds.x = 0;
			m->vtxs[1].cds.x = x_stride;
			m->vtxs[2].cds.x = x_stride;
			m->vtxs[3].cds.x = 0;
		}
	}
}
