#pragma once

#include <glm/glm.hpp>
using namespace glm;

namespace cam {
	extern mat4
		trns,
		rotn,
		mvp;

	extern void update();
};
