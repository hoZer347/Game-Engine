#include "Text.h"

FT_Library lib;
std::vector<Font*> FONT;

void Text::add(char c) {
	if (c == '\n') {
		x = 0;
		y += f->scale;
		return;
	}

	Letter* l = f->letters[c];
	Mesh* m = create_square(false);

	m->vtxs[BOTTOM_LEFT].pos	= vec3(x +    0 + l->x_offset, -y        + l->y_offset, 0);
	m->vtxs[BOTTOM_RIGHT].pos	= vec3(x + l->w + l->x_offset, -y        + l->y_offset, 0);
	m->vtxs[TOP_RIGHT].pos		= vec3(x + l->w + l->x_offset, -y - l->h + l->y_offset, 0);
	m->vtxs[TOP_LEFT].pos		= vec3(x +    0 + l->x_offset, -y - l->h + l->y_offset, 0);
	
	std::reverse(m->vtxs.begin(), m->vtxs.end());

	l->m->ortho = f->ortho;

	letters.push_back({ c, l->m->vtxs.size() });

	for (auto& v : m->vtxs) {
		v.pos *= 1. / f->scale;
		l->m->inds.push_back(l->m->inds.size());
		l->m->vtxs.push_back(v);
	}

	x += l->x_buffer;

	w = std::max(w, x);
	h = std::max(h, y);
}

vec3 Text::get_v(unsigned char i) {
	switch (i) {
	case BOTTOM_LEFT:
		return pos + vec3(0,  0, 0) /= f->scale;
	case BOTTOM_RIGHT:
		return pos + vec3(w,  0, 0) /= f->scale;
	case TOP_RIGHT:
		return pos + vec3(w, h, 0) /= f->scale;
	case TOP_LEFT:
		return pos + vec3(0, h, 0) /= f->scale;
	default:
		return vec3(0, 0, 0);
	}
}
