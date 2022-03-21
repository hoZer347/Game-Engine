#pragma once

#include <glm/glm.hpp>
using namespace glm;

namespace cam {
	struct lightSource {
		mat4
			mode = mat4(1),
			view = mat4(1),
			proj = mat4(1),
			mvp  = mat4(1);
	};

	extern mat4
		trns,
		roll,
		ptch,
		yaww,
		mode,
		view,
		proj,
		mvp;

	extern void create();

	extern void close();
};
