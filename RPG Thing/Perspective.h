#pragma once

#include <glm/glm.hpp>
using namespace glm;

namespace perspective {
	struct Perspective {

		// Perspective Variables
		mat4
			mode = mat4(1),
			view = mat4(1),
			proj = mat4(1),
			mvp  = mat4(1);

		// Rendering Quad Variables
		mat4
			trns = mat4(1),
			rotn = mat4(1);
	};

	void load(Perspective*);

	namespace camera {
		extern Perspective* create();
		extern void del(Perspective*);
	};

	namespace light {
		extern Perspective* create();
		extern void del(Perspective*);
	};
};

