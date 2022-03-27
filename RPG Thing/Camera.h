#pragma once

#include <glm/glm.hpp>
using namespace glm;

namespace cam {
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
