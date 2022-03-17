#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
using namespace glm;

namespace geo {
	class Geo;

	namespace square {
		extern Geo* create();
	};

	namespace cube {
		extern Geo* create();
	};

	extern void add_texture(Geo*, const char*);
};

