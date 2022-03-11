#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "Object.h"
using namespace obj;

#include <vector>

namespace mesh {
	class Mesh : public Obj {
	public:
		~Mesh();
		void add_attrib(unsigned char size);
		void set_shader(const char*);
		vec4 pos(unsigned int = 0);
		void pump(std::vector<float>&);
		void pump(std::vector<unsigned int>&);
		void setup();
		void update();
		void render();

		mat4 trns = mat4(1);

	protected:
		unsigned int
			stride=0,
			shader=0,
			drawing_mode=0;

		std::vector<float> vtxs;
		std::vector<unsigned int> inds;
		std::vector<std::pair<unsigned int, unsigned int>> atbs;
	};
}
