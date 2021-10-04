#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#include <vector>

using namespace glm;

struct Vtx {
	vec3 pos;
	vec4 clr = {1, 1, 1, 1};
};

struct Tex {
	std::vector<vec3> pos;
	std::vector<vec2> cds;
};

struct Tri {
	Vtx *v1=NULL, *v2=NULL, *v3=NULL;
};
