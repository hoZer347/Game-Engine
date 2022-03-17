#pragma once

#include "glm/glm.hpp"
using namespace glm;

#include <vector>

namespace sprite {
	class Sprite;

	extern Sprite* create(const char*, vec2, vec2);
	extern void del(Sprite*);
	extern mat4& trns(Sprite*);
	extern vec2& curr(Sprite*);
}
