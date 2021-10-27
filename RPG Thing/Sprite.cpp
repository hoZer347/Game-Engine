#include "Sprite.h"

std::vector<Sprite*> SPRS;

void Sprite::update() {
	if (curr_time - last_time >= interval && mesh->gl_texture) {
		last_time = curr_time;

		bool reset = false;

		for (auto& i : mesh->vtxs) {
			i.cds.x += x_stride;
			if (i.cds.x > 1) {
				reset = true;
				break;
			}
		}

		if (reset) {
			mesh->vtxs[0].cds.x = 0;
			mesh->vtxs[1].cds.x = x_stride;
			mesh->vtxs[2].cds.x = x_stride;
			mesh->vtxs[3].cds.x = 0;
		}
	}
}
