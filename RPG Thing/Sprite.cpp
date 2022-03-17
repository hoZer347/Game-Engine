#include "Sprite.h"

#include "Mesh.h"

#include "Camera.h"

#include "GLFW/glew.h"

#define GLM_FORCE_RADIANS
#include "glm/gtx/transform.hpp"
using namespace glm;

#include <iostream>

namespace sprite {
	class Sprite :
		public mesh::Mesh {
	public:
		Sprite();
		void setup();
		void update();
		void render();
		void next();

		ivec2
			dims;
		vec2
			curr,
			stride;
	};



	class SpriteManager :
		public obj::Manager<Sprite> {
	public:
		void update();

	private:
		unsigned char
			interval=15,
			curr=0;
		bool
			animate=true;
	};

	SpriteManager SPRITE;



	Sprite::Sprite() {
		add_attrib(3);

		set_shader(
			"Position_Basic.vert",
			"Sprites_Basic.geom",
			"Texture_Basic.frag");

		drawing_mode = GL_POINTS;
	};
	void Sprite::setup() {
		glUseProgram(shader);

		vtxs = {
			0, 0, 0
		};

		inds = {
			0
		};

		glBindTexture(GL_TEXTURE_2D, texs[0]);
		glGetTexLevelParameteriv(
			GL_TEXTURE_2D, 0,
			GL_TEXTURE_WIDTH,
			&dims.x);
		glGetTexLevelParameteriv(
			GL_TEXTURE_2D, 0,
			GL_TEXTURE_HEIGHT,
			&dims.y);
		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER,
			GL_NEAREST);
		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER,
			GL_NEAREST);
		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_S,
			GL_REPEAT);

		stride /= dims;
		curr.y += 1 - stride.y;

		glUniform2fv(
			glGetUniformLocation(shader, "stride"),
			1, &stride[0]);
		glUniform2fv(
			glGetUniformLocation(shader, "start"),
			1, &curr[0]);

		glBindTexture(GL_TEXTURE_2D, 0);

		Mesh::setup();
	};
	void Sprite::render() {
		glUseProgram(shader);
		glUniformMatrix4fv(
			glGetUniformLocation(shader, "mvp"),
			1, GL_FALSE, &cam::mvp[0][0]);
		glUniformMatrix4fv(
			glGetUniformLocation(shader, "trns"),
			1, GL_FALSE, &trns[0][0]);
		Mesh::render();
	};
	void Sprite::update() {
		Mesh::update();
	};
	void Sprite::next() {
		glUseProgram(shader);
		curr.x += stride.x;
		glUniform2fv(
			glGetUniformLocation(shader, "start"),
			1, &curr[0]);
	};



	void SpriteManager::update() {
		if (animate) {
			curr++;
			if (curr > interval) {
				curr = 0;
				for (auto& s : objs)
					s->next();
			}
		}
	};



	Sprite* create(const char* file_name, vec2 stride, vec2 start) {
		Sprite* s = SPRITE.create();

		s->add_texture(file_name);

		s->stride = stride;
		s->curr = start;

		return s;
	};
	void del(Sprite* s) {
		SPRITE.del(s);
	};
	vec2& curr(Sprite* s) {
		return s->curr;
	};
};
