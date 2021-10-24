#pragma once

#define GLM_FORCE_RADIANS

#include <GLFW/glew.h>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>

#include <map>
#include <memory>
#include <vector>
#include <iostream>

using namespace glm;

struct Vtx; struct Mesh;

extern std::vector<Vtx> VTXS;
extern std::vector<unsigned int> INDS;
extern std::vector<Mesh> MESH;
extern std::map<const char*, unsigned int> TEXS;

// Represents a vertex in the world
struct Vtx {
	vec3 pos = vec3(0);
	vec4 clr = vec4(1);
	vec3 nrm = { 0, 1, 0 };
	vec2 cds = vec2(-1);
};

// Represents a mesh of vertices, with rendering variables such as the way to render it + the texture location
struct Mesh {
	unsigned int
		index = 0,
		begin = 0,
		size = 0,
		gl_render_type = GL_TRIANGLES,
		gl_data_type = GL_UNSIGNED_INT,
		gl_texture = 0,
		gl_shader = 0;

	void operator=(vec3 v) {
		vec3 d = v - VTXS[begin].pos;
		VTXS[begin].pos = v;

		for (unsigned int i = begin+1; i < begin + size; i++)
			VTXS[i].pos += d;
	}
	void operator+=(vec3 v) {
		for (unsigned int i = begin; i < begin + size; i++)
			VTXS[i].pos += v;
	};
	void operator-=(vec3 v) {
		for (unsigned int i = begin; i < begin + size; i++)
			VTXS[i].pos -= v;
	};
	void operator*=(int v) {
		for (unsigned int i = begin; i < begin + size; i++)
			VTXS[i].pos *= v;
	};
	void operator/=(int v) {
		for (unsigned int i = begin; i < begin + size; i++)
			VTXS[i].pos /= v;
	};
	void operator*=(mat4 m) {
		for (unsigned int i = begin; i < begin + size; i++)
			VTXS[i].pos = vec3(vec4(VTXS[i].pos, 1) * m);
	}
};

// Represents a series of meshes that all fall within one object
struct Renderable {
	const char* name = "";

	unsigned int
		begin = 0,
		size = 0;
	
	void operator=(vec3 v) {
		for (unsigned int i = begin; i < begin + size; i++)
			MESH[i] = v;
	};
	void operator+=(vec3 v) {
		for (unsigned int i = begin; i < begin + size; i++)
			MESH[i] += v;
	};
	void operator-=(vec3 v) {
		for (unsigned int i = begin; i < begin + size; i++)
			MESH[i] -= v;
	};
	void operator*=(int v) {
		for (unsigned int i = begin; i < begin + size; i++)
			MESH[i] *= v;
	};
	void operator/=(int v) {
		for (unsigned int i = begin; i < begin + size; i++)
			MESH[i] /= v;
	};
	void operator*=(mat4 m) {
		for (unsigned int i = begin; i < begin + size; i++)
			MESH[i] *= m;
	}
};

// Generates a mesh object
static Mesh& create_mesh(
	std::vector<Vtx>& vtxs,
	std::vector<unsigned int>& inds,
	unsigned int gl_render_type = GL_TRIANGLES,
	unsigned int gl_data_type = GL_UNSIGNED_INT,
	unsigned int gl_texture = 0,
	unsigned int gl_shader = 0) {

	Mesh m;

	m.index = MESH.size();
	m.begin = INDS.size();

	for (auto& i : vtxs)
		VTXS.push_back(i);

	for (auto& i : inds)
		INDS.push_back(i + m.begin);

	m.size = inds.size();

	m.gl_render_type = gl_render_type;
	m.gl_data_type = gl_data_type;
	m.gl_texture = gl_texture;
	m.gl_shader = gl_shader;

	MESH.push_back(m);

	return MESH.back();
}

// Safely deletes a mesh object
static void delete_mesh(Mesh& m) {

	// Decrementing greater indexed meshes
	for (unsigned int i = m.index+1; i < MESH.size(); i++) {
		MESH[i].index--;
		MESH[i].begin -= m.size;
	}

	// Decrementing greater indices
	for (unsigned int i = m.begin + m.size; i < INDS.size(); i++)
		INDS[i] -= m.size;
	
	// Finding vertex deletion range
	unsigned int min = VTXS.size(), max = 0;

	for (unsigned int i = m.begin; i <= m.begin + m.size; i++) {
		min = std::min(INDS[i], min);
		max = std::max(INDS[i], max);
	}

	// Deleting stuff
	VTXS.erase(VTXS.begin() + min, VTXS.begin() + max + 1);
	INDS.erase(INDS.begin() + m.begin, INDS.begin() + m.begin + m.size);
	MESH.erase(MESH.begin() + m.index);
}

// Generates a texture and attaches it to the provided mesh
static void bind_texture(const char* file_name, Mesh& m) {
	if (TEXS[file_name]) {
		m.gl_texture = TEXS[file_name];
		return;
	}

	m.gl_texture = SOIL_load_OGL_texture(file_name, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);

	if (m.gl_texture) {
		glBindTexture(GL_TEXTURE_2D, m.gl_texture);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		TEXS[file_name] = m.gl_texture;
	}
}

// Generates a plane (0, 0, 0) -> (1, 1, 0), facing +Z, by default
static Mesh& create_square() {
	std::vector<Vtx> vtxs = { Vtx(), Vtx(), Vtx(), Vtx() };

	vtxs[0] = Vtx({ vec3(0, 0, 0), vec4(1), vec3(0, 0, 1), vec2(0, 0) });
	vtxs[1] = Vtx({ vec3(1, 0, 0), vec4(1), vec3(0, 0, 1), vec2(1, 0) });
	vtxs[2] = Vtx({ vec3(1, 1, 0), vec4(1), vec3(0, 0, 1), vec2(1, 1) });
	vtxs[3] = Vtx({ vec3(0, 1, 0), vec4(1), vec3(0, 0, 1), vec2(0, 1) });

	std::vector<unsigned int> inds = { 0, 1, 2, 3 };

	return create_mesh(vtxs, inds, GL_QUADS);
}


