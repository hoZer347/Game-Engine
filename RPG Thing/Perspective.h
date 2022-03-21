#pragma once

#include <glm/glm.hpp>
using namespace glm;

namespace perspective {
	struct Perspective {
		mat4

		// Perspective Variables
			mode = mat4(1),
			view = mat4(1),
			proj = mat4(1),
			mvp  = mat4(1),

		// Rendering Quad Variables
			roll = mat4(1),
			yaww = mat4(1),
			ptch = mat4(1),
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
