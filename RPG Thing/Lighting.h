#pragma once

#include "glm/glm.hpp"
using namespace glm;

namespace depth {
	extern unsigned int
		depth_map;

	extern
		mat4 lightMat;

	class DepthMapper;

	extern void create();
	extern void close();
};
