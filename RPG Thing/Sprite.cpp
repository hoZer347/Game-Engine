#include "Sprite.h"

#include "Mesh.h"
using namespace mesh;

#include "Camera.h"
#include "Textures.h"

#include "GLFW/glew.h"

#define GLM_FORCE_RADIANS
#include "glm/gtx/transform.hpp"
using namespace glm;

#include <iostream>

// TODO: syncronize with time, not framerate

namespace sprite {
	class Sprite :
		public Mesh {
	public:
		Sprite();
		void set_texture(const char*);
		void setup();
		void render();
		void next();

		unsigned int
			texture=0;
		ivec2
			dims;
		vec2
			stride;
		vec4
			curr;
	};



	class SpriteManager :
		public Manager<Sprite> {
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
		drawing_mode = GL_POINTS;

		add_attrib(3);

		set_shader("Sprites_Basic");
	};
	void Sprite::set_texture(const char* file_name) {
		texture = texture::create(file_name);
	};
	void Sprite::setup() {
		Mesh::setup();
		glBindTexture(GL_TEXTURE_2D, texture);
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
		glUniform1i(
			glGetUniformLocation(shader, "tex"),
			GL_TEXTURE0 + texture);

		glBindTexture(GL_TEXTURE_2D, 0);
	};
	void Sprite::render() {
		glUseProgram(shader);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniformMatrix4fv(
			glGetUniformLocation(shader, "mvp"),
			1, GL_FALSE, &cam::mvp[0][0]);
		glUniformMatrix4fv(
			glGetUniformLocation(shader, "trns"),
			1, GL_FALSE, &trns[0][0]);
		Mesh::render();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
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



	Sprite* create(const char* file_name, vec2 stride, vec4 start) {
		Sprite* s = SPRITE.create();

		s->set_texture(file_name);
		s->stride = stride;
		s->curr = start;

		return s;
	};
	mat4& trns(Sprite* s) {
		return s->trns;
	}
	void pump(Sprite* s, std::vector<float>& vtxs) {
		s->pump(vtxs);
	};

	void pump(Sprite* s, std::vector<unsigned int>& inds) {
		s->pump(inds);
	};
};
