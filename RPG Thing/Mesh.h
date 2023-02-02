#pragma once

#include "Object.h"

#include <vector>

namespace mesh {
	struct Mesh : obj::Obj {
		Mesh();
		~Mesh();
		void stage(unsigned char&);
		void update_buffers();
		void pump(std::vector<float>&);
		void pump(std::vector<unsigned int>&);

		unsigned int
			shader=0,
			gl_render_type=0,
			fbo=0, ebo=0;

		std::vector<float> data;
		std::vector<unsigned int> inds;
		std::vector<unsigned int> texs;

	protected:
		void stg_update();
		void stg_render();
	};

	void create();
};
