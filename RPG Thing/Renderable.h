#pragma once

#define GLM_FORCE_RADIANS

#include <GLFW/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <iostream>

using namespace glm;

struct Vtx {
	vec3 pos = { 0, 0, 0 };
	vec4 clr = { 1, 1, 1, 1 };
	vec3 nrm = { 0, 1, 0 };
	vec2 cds = { -1, -1 };
};

struct IndexObj {
	std::vector<unsigned int> inds = {};
	const char* name = "";

	unsigned int
		gl_render_type = GL_TRIANGLES,
		gl_data_type = GL_UNSIGNED_INT,
		gl_buffer = 0,
		texture = 0;
};

struct Renderable {
	IndexObj* i = NULL;
	std::vector<Vtx>* vtxs = NULL;
	std::vector<unsigned int>* inds;
};

static void translate(Renderable& r, vec3 v) {
	for (auto& i : *r.inds)
		(*r.vtxs)[i].pos += v;
}

static void create_planes(Renderable* faces, Renderable* lines, int x, int y) {
	int index = 0;

	if (faces && faces->vtxs)
		index = faces->vtxs->size();
	else if (lines && lines->vtxs)
		index = lines->vtxs->size();
	else
		return;

	if (faces && faces->vtxs) {
		for (int i = 0; i <= x; i++)
			for (int j = 0; j <= y; j++)
				faces->vtxs->push_back(Vtx({ vec3(i, 0, -j), vec4(1, 1, 1, 1), vec3(0, 1, 0) }));

		for (int i = 0; i < x; i++)
			for (int j = 0; j < y; j++) {
				faces->inds->push_back(index + i * y + i + j);
				faces->inds->push_back(index + i * y + i + j + y + 1);
				faces->inds->push_back(index + i * y + i + j + y + 2);
				faces->inds->push_back(index + i * y + i + j + 1);
			}
	}

	if (lines && lines->inds) {
		if (!faces || !faces->vtxs)
			for (int i = 0; i <= x; i++)
				for (int j = 0; j <= y; j++)
					lines->vtxs->push_back(Vtx({ vec3(i, 0, -j) }));

		for (int i = 0; i <= x; i++)
			for (int j = 0; j <= y; j++) {
				if (j < y) {
					lines->inds->push_back(index + i * y + i + j);
					lines->inds->push_back(index + i * y + i + j + 1);
				}
				if (i < x) {
					lines->inds->push_back(index + i * y + i + j);
					lines->inds->push_back(index + i * y + i + j + y + 1);
				}
			}
	}
}
