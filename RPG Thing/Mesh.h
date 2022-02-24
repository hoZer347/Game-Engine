#pragma once

#include "Object.h"

#include "glm/glm.hpp"
using namespace glm;

#include <vector>

namespace mesh {
	enum {
		LINES,
		TRIANGLES,
		QUADS,
	};

	class Mesh : public obj::Obj<Mesh> {
	public:
		~Mesh();
		void add_attrib(unsigned char);
		void pump(std::vector<float>&, unsigned int);
		void pump(std::vector<unsigned int>&, unsigned int);
		void setup();
		void update();
		void render();
		virtual void draw() = 0;

	protected:
		unsigned int
			_vtxs = 0,
			_inds = 0,
			shader = 0,
			stride = 0;

		std::vector<unsigned int> atbs;
		std::vector<unsigned int> inds;
		std::vector<float> vtxs;
	};
	
	class Lines : public Mesh {
	public:
		void setup();
		void update();
		void draw();

		float width = 1;
		vec4 color = vec4(0, 0, 0, 1);
	};

	class Triangles : public Mesh {
	public:
		void draw();
	};

	class Quads : public Mesh {
	public:
		void draw();
	};
}
