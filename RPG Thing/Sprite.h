#pragma once

#include "glm/glm.hpp"
using namespace glm;

#include <vector>

namespace sprite {
	class Sprite;

	extern Sprite* create(const char*, vec2=vec2(32), vec2=vec2(0));
	extern void del(Sprite*);
	extern vec2& curr(Sprite*);
}
