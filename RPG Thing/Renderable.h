#pragma once

#include <glm/glm.hpp>

#include <vector>

using namespace glm;

struct Vtx {
	vec3 pos;
	vec4 clr = {1, 1, 1, 1};
};

struct Tex {
	vec3 pos;
	vec2 cds;
};

struct Tri {
	Vtx *v1=NULL, *v2=NULL, *v3=NULL;
};

struct Spr {
	Tex *t1=NULL, *t2=NULL, *t3=NULL, *t4=NULL;
};
