#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
using namespace glm;

namespace geo {
	namespace square {
		class Square;

		extern Square* create();
		extern void del(Square*);
	};
};

