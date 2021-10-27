#pragma once

#define GLM_FORCE_RADIANS

#include <GLFW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SOIL/SOIL.h>

#include <map>
#include <vector>

#include <memory>
#include <iostream>

using namespace glm;

struct Mesh;

extern std::vector<Mesh*> MESH;
extern std::map<const char*, unsigned int> TEXS;

// Represents a vertex in the world
struct Vtx {
	vec3 pos = vec3(0);
	vec4 clr = vec4(1);
	vec3 nrm = { 0, 0, 1 };
	vec2 cds = vec2(-1);
};

// Represents a mesh of vertices, with rendering variables such as the way to render it + the texture location
struct Mesh {
	std::vector<Vtx> vtxs;
	std::vector<unsigned int> inds;
	mat4 trns = mat4(1);

	unsigned int
		index = 0,
		gl_render_type = GL_QUADS,
		gl_data_type = GL_UNSIGNED_INT,
		gl_texture = 0,
		gl_shader = 0;
};

// Generates a mesh object
static Mesh* create_mesh(
	std::vector<Vtx>& vtxs,
	std::vector<unsigned int>& inds,
	unsigned int gl_render_type = GL_QUADS,
	unsigned int gl_data_type = GL_UNSIGNED_INT,
	unsigned int gl_texture = 0,
	unsigned int gl_shader = 0) {

	Mesh* m = new Mesh();

	m->index = MESH.size();

	for (auto& i : vtxs)
		m->vtxs.push_back(i);

	for (auto& i : inds)
		m->inds.push_back(i);

	m->gl_render_type = gl_render_type;
	m->gl_data_type = gl_data_type;
	m->gl_texture = gl_texture;
	m->gl_shader = gl_shader;

	MESH.push_back(m);

	return MESH.back();
}

// CREATION / DELETION FUNCTIONS

// Safely Deletes a Mesh
static void delete_mesh(Mesh* m) {
	for (auto& i : MESH)
		if (m->index > m->index)
			i->index--;

	MESH.erase(MESH.begin() + m->index);
}

// Generates a square (0, 0, 0) -> (1, 1, 0), facing +Z, by default
static Mesh* create_square() {
	std::vector<Vtx> vtxs = { Vtx(), Vtx(), Vtx(), Vtx() };

	vtxs[0] = Vtx({ vec3(0, 0, 0), vec4(1), vec3(0, 0, 1), vec2(0, 0) });
	vtxs[1] = Vtx({ vec3(1, 0, 0), vec4(1), vec3(0, 0, 1), vec2(1, 0) });
	vtxs[2] = Vtx({ vec3(1, 1, 0), vec4(1), vec3(0, 0, 1), vec2(1, 1) });
	vtxs[3] = Vtx({ vec3(0, 1, 0), vec4(1), vec3(0, 0, 1), vec2(0, 1) });

	std::vector<unsigned int> inds = { 0, 1, 2, 3 };

	return create_mesh(vtxs, inds);
}

// Generates a plane of squares of the given dimensions with the default inner square dimensions
static Mesh* create_plane(unsigned int x, unsigned int y) {
	std::vector<Vtx> vtxs;
	std::vector<unsigned int> inds;

	unsigned int index = 0;

	for (unsigned int i = 0; i < x; i++)
		for (unsigned int j = 0; j < y; j++) {
			vtxs.push_back(Vtx({ vec3(i    , j    , 0), vec4(1), vec3(0, 0, 1), vec2(0, 0) }));
			vtxs.push_back(Vtx({ vec3(i + 1, j    , 0), vec4(1), vec3(0, 0, 1), vec2(1, 0) }));
			vtxs.push_back(Vtx({ vec3(i + 1, j + 1, 0), vec4(1), vec3(0, 0, 1), vec2(1, 1) }));
			vtxs.push_back(Vtx({ vec3(i    , j + 1, 0), vec4(1), vec3(0, 0, 1), vec2(0, 1) }));
			inds.push_back(index++);
			inds.push_back(index++);
			inds.push_back(index++);
			inds.push_back(index++);
		}

	return create_mesh(vtxs, inds);
}

// TEXTURE FUNCTIONS

// Generates a texture and attaches it to the provided mesh
static void bind_texture(const char* file_name, Mesh* m) {
	if (TEXS[file_name]) {
		m->gl_texture = TEXS[file_name];
		return;
	}

	m->gl_texture = SOIL_load_OGL_texture(file_name, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);

	if (m->gl_texture) {
		glBindTexture(GL_TEXTURE_2D, m->gl_texture);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		TEXS[file_name] = m->gl_texture;
	}
}

// RENDERING FUNCTIONS

// Changes how openGL will render the given mesh (GL_LINES, GL_TRIANGLES, etc.)
static void change_rendering(Mesh* m, unsigned int gl_render_type) {
	std::vector<unsigned int> new_inds;

	unsigned int index = 0;

	switch (m->gl_render_type) {

		case GL_QUADS:
			
			switch (gl_render_type) {

			case GL_LINES:

				for (unsigned int i = 0; i < m->inds.size(); i+=4) {
					new_inds.push_back(m->inds[index++]);
					new_inds.push_back(m->inds[index]);
					new_inds.push_back(m->inds[index++]);
					new_inds.push_back(m->inds[index]);
					new_inds.push_back(m->inds[index++]);
					new_inds.push_back(m->inds[index]);
					new_inds.push_back(m->inds[index++]);
					new_inds.push_back(m->inds[index-4]);
				}

				break;
			}
			break;
	}

	m->inds = new_inds;
	m->gl_render_type = gl_render_type;
}
