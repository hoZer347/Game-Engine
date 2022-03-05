#pragma once

#include "glm/glm.hpp"
using namespace glm;

#include <vector>

namespace sprite {
	class Sprite;

	extern Sprite* create(const char*, vec2, vec4);
	extern void pump(Sprite*, std::vector<float>&);
	extern void pump(Sprite*, std::vector<unsigned int>&);
}
