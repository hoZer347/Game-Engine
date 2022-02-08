#include "Text.h"

FT_Library lib;
std::vector<Text*> TEXT;
std::vector<unsigned int> _TEXT;
std::vector<Font*> FONT;
std::vector<unsigned int> _FONT;
std::vector<unsigned int> FTXS;

void Text::add(unsigned char c, Font* f) {
	Mesh* _m = create_square(false);

	Letter* l = f->letters[c];
	
	vec3 v1 = vec3(l->s, 0)/=64;
	vec3 v2 = vec3(l->b, 0)/=64;

	_m->vtxs[0].pos = vec3(0, 0, 0) * v1 + v2 + stride;
	_m->vtxs[1].pos = vec3(1, 0, 0) * v1 + v2 + stride;
	_m->vtxs[2].pos = vec3(1, 1, 0) * v1 + v2 + stride;
	_m->vtxs[3].pos = vec3(0, 1, 0) * v1 + v2 + stride;

	vec2 v3 = l->s/f->s;
	vec2 v4 = vec2(l->x, 0)/f->s;

	_m->vtxs[0].cds = vec2(0,  0) * v3 + v4;
	_m->vtxs[1].cds = vec2(1,  0) * v3 + v4;
	_m->vtxs[2].cds = vec2(1, -1) * v3 + v4;
	_m->vtxs[3].cds = vec2(0, -1) * v3 + v4;

	m->add(_m);

	for (auto& v : _m->vtxs) {
		min.x = std::min(v.pos.x, min.x);
		min.y = std::min(v.pos.y, min.y);
		max.x = std::max(v.pos.x, max.x);
		max.y = std::max(v.pos.y, max.y);
	}

	delete _m;

	stride += vec3(l->a, 0) /= (64 * 64);
}

vec3 Text::pos(unsigned char i) {
	switch (i) {
	case BOTTOM_LEFT:
		return vec3(m->trns * vec4(min,			 0, 1));
	case BOTTOM_RIGHT:
		return vec3(m->trns * vec4(max.x, min.y, 0, 1));
	case TOP_RIGHT:
		return vec3(m->trns * vec4(max,			 0, 1));
	case TOP_LEFT:
		return vec3(m->trns * vec4(min.x, max.y, 0, 1));
	default:
		return vec3(0);
	}
}
