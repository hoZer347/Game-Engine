#include "Sprite.h"

#include "Mesh.h"
using namespace mesh;

#include "GLFW/glew.h"

#define GLM_FORCE_RADIANS
#include "glm/gtx/transform.hpp"

#include <iostream>

namespace sprite {
	class Sprite :
		public Texture {
	public:
		Sprite();
		void setup();
		void next();

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
	};

	SpriteManager SPRITE;



	Sprite::Sprite() {
		drawing_mode = GL_POINTS;

		add_attrib(3);

		set_shader("Sprites_Basic");
	};
	void Sprite::setup() {
		Texture::setup();
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
		glBindTexture(GL_TEXTURE_2D, 0);

		stride /= dims;
		curr.y += 1 - stride.y;

		glUniform2fv(glGetUniformLocation(shader, "stride"), 1, &stride[0]);
		glUniform2fv(glGetUniformLocation(shader, "start"), 1, &curr[0]);
	};
	void Sprite::next() {
		glUseProgram(shader);
		curr.x += stride.x;
		glUniform2fv(glGetUniformLocation(shader, "start"), 1, &curr[0]);
	};



	void SpriteManager::update() {
		curr++;
		if (curr > interval) {
			curr = 0;
			for (auto& s : objs)
				s->next();
		}
	};



	Sprite* create(const char* file_name, vec2 stride, vec4 start) {
		Sprite* s = SPRITE.create();

		s->set_texture(file_name);
		s->stride = stride;
		s->curr = start;

		return s;
	};

	void pump(Sprite* s, std::vector<float>& vtxs) {
		s->pump(vtxs);
	};

	void pump(Sprite* s, std::vector<unsigned int>& inds) {
		s->pump(inds);
	};
};
