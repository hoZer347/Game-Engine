#pragma once

#include "Mesh.h"
#include "Timer.h"

class Sprite : public MeshObj {
public:
	void update();

	int last_time = curr_time;
	int interval = 16 * 15;
	float sprite_size=32;
	int x=0, y=0;
	int img_x=0, img_y=0;
	float x_stride=0, y_stride=0;
};

static Sprite* create_sprite(float sprite_size=32, int interval=16*15, bool animate=true) {
	Sprite* s = new Sprite();
	s->m = create_square();
	s->animate = animate;

	s->interval = interval;
	s->sprite_size = sprite_size;

	OBJS.push_back(s);

	return s;
}

static void bind_texture(Sprite* s, const char* file_name="Textures/Anna.png") {
	bind_texture(file_name, s->m);

	glBindTexture(GL_TEXTURE_2D, s->m->gl_texture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &s->img_x);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &s->img_y);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	s->x_stride = s->sprite_size / (float)s->img_x;
	s->y_stride = s->sprite_size / (float)s->img_y;

	s->m->vtxs[0].cds = { 0, 1 - 2 * s->y_stride };
	s->m->vtxs[1].cds = { s->x_stride, 1 - 2 * s->y_stride };
	s->m->vtxs[2].cds = { s->x_stride, 1 - s->y_stride };
	s->m->vtxs[3].cds = { 0, 1 - s->y_stride };
}
