#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
using namespace glm;

#include "Object.h"

#include <vector>

namespace mesh {
	class Mesh : public obj::Obj {
	public:
		Mesh();
		~Mesh();
		void add_attrib(unsigned char size);
		void add_texture(const char*);
		void add_texture(unsigned int);
		void set_shader(const char*);
		void set_shader(const char*, const char*);
		void set_shader(const char*, const char*, const char*);
		void set_shader(unsigned int);
		vec4 pos(unsigned int=0);
		void pump(std::vector<float>&);
		void pump(std::vector<unsigned int>&);
		void setup();
		void update();
		void render();

		mat4 trns = mat4(1);

		bool
			opaque = true;

	protected:
		unsigned int
			drawing_mode = 0,
			_vtxs=0,
			_inds=0,
			stride=0,
			shader=0;

		std::vector<float> vtxs;
		std::vector<unsigned int> inds;
		std::vector<unsigned int> texs;
		std::vector<std::pair<unsigned int, unsigned int>> atbs;
	};

	extern mat4& trns(void*);

	extern std::vector<Mesh*> MESH;
}
