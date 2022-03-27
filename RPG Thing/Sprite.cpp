#include "Sprite.h"

#include "Mesh.h"
#include "Camera.h"
#include "shaders.h"

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
	Sprite::Sprite() {
		add_attrib(3);

		drawing_mode = GL_POINTS;
	};
	void Sprite::setup() {
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

		glBindTexture(GL_TEXTURE_2D, 0);

		Mesh::setup();
	};
	void Sprite::render() {
		glUniform2fv(
			glGetUniformLocation(shader, "stride"),
			1, &stride[0]);
		glUniform2fv(
			glGetUniformLocation(shader, "start"),
			1, &curr[0]);
		glUniformMatrix4fv(
			glGetUniformLocation(shader, "trns"),
			1, GL_FALSE, &trns[0][0]);
		Mesh::render();
	};
	void Sprite::update() {
		Mesh::update();
	};
	void Sprite::next() {
		curr.x += stride.x;
	};



	class SpriteManager :
		public obj::Manager<Sprite> {
	public:
		void update();
		void render();

		unsigned char
			interval=15,
			shader=0,
			curr=0;
		bool
			animate=true;
	};
	void SpriteManager::update() {
		glUseProgram(shader);
		if (animate) {
			curr++;
			if (curr > interval) {
				curr = 0;
				for (auto& s : objs)
					s->next();
			}
		}
	};
	void SpriteManager::render() {
		glUseProgram(shader);

		glUniformMatrix4fv(
			glGetUniformLocation(shader, "mvp"),
			1, GL_FALSE, &cam::mvp[0][0]);

		obj::Manager<Sprite>::render();
	};

	SpriteManager SPRITE;



	Sprite* create(const char* file_name, vec2 stride, vec2 start) {
		Sprite* s = SPRITE.create();

		s->add_texture(file_name);
		if (!SPRITE.shader)
			SPRITE.shader = shader::create(
				"Position_Basic.vert",
				"Sprites_Basic.geom",
				"Texture_Basic.frag");
		s->shader = SPRITE.shader;
		s->stride = stride;
		s->curr = start;

		s->setup();

		return s;
	};
	void del(Sprite* s) {
		SPRITE.del(s);
	};
	vec2& curr(Sprite* s) {
		return s->curr;
	};
};
