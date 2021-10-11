#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#include <memory>
#include <vector>

using namespace glm;

struct Vtx {
	vec3 pos;
	vec4 clr = { 1, 1, 1, 1 };
	vec3 nrm = { 0, 1, 0 };
	vec2 cds = { 1, 1 };
};

struct Tri {
	std::shared_ptr<Vtx> v1, v2, v3;
};

struct Pln {
	std::shared_ptr<Vtx> v1, v2, v3, v4;
};

struct Rpsm {
	std::shared_ptr<Tri> t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;
	std::shared_ptr<Pln> p1, p2, p3, p4, p5, p6;
};
