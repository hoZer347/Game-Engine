#pragma once

#include "Renderable.h"
#include "Timer.h"

class Sprite {
public:
	operator Mesh* () { return mesh; }
	void update();

	int last_time = curr_time;
	int interval = 16 * 15;
	float sprite_size=32;
	int x=0, y=0;
	int img_x=0, img_y=0;
	float x_stride=0, y_stride=0;

	Mesh* mesh=NULL;
};

extern std::vector<Sprite*> SPRS;

static Sprite* create_sprite(float sprite_size=32, int interval= 16 * 15) {
	Sprite* s = new Sprite();
	s->mesh = create_square();

	s->interval = interval;
	s->sprite_size = sprite_size;

	SPRS.push_back(s);

	return s;
}

static void bind_texture(const char* file_name, Sprite* s) {
	bind_texture(file_name, s->mesh);

	glBindTexture(GL_TEXTURE_2D, s->mesh->gl_texture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &s->img_x);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &s->img_y);
	glBindTexture(GL_TEXTURE_2D, 0);

	s->x_stride = s->sprite_size / (float)s->img_x;
	s->y_stride = s->sprite_size / (float)s->img_y;

	s->mesh->vtxs[0].cds = { 0, 1 - 2 * s->y_stride };
	s->mesh->vtxs[1].cds = { s->x_stride, 1 - 2 * s->y_stride };
	s->mesh->vtxs[2].cds = { s->x_stride, 1 - s->y_stride };
	s->mesh->vtxs[3].cds = { 0, 1 - s->y_stride };

	std::cout << s->x_stride << std::endl;
	std::cout << s->y_stride << std::endl;
}