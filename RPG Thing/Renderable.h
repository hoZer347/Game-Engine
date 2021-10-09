#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#include <vector>

using namespace glm;

struct Vtx {
	vec3 pos;
	vec4 clr = { 1, 1, 1, 1 };
	vec3 nrm;
	vec2 cds = { 1, 1 };
};
