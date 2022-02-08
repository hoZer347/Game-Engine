#pragma once

#include <GLFW/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <SOIL/SOIL.h>
#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <map>

#include <iostream>

using namespace glm;

enum {
	BOTTOM_LEFT = 0,
	BOTTOM_RIGHT = 1,
	TOP_RIGHT = 2,
	TOP_LEFT = 3
};

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
	bool ortho = false;
	bool show = true;
	unsigned int index = 0;
	mat4 trns = mat4(1);
	void add(Mesh* m) {
		unsigned int index = vtxs.size();

		std::reverse(m->vtxs.begin(), m->vtxs.end());

		for (auto& v : m->vtxs)
			vtxs.push_back(v);
		for (auto& i : m->inds)
			inds.push_back(index + i);
	}
	vec3 pos(int i=0) { return vec3(trns * vec4(vtxs[i].pos, 1)); }

	unsigned int
		gl_render_type = GL_QUADS,
		gl_data_type = GL_UNSIGNED_INT,
		gl_texture = 0;
};

// Wrapper for meshes that need to be periodically updated
class _MeshObj {
public:
	virtual void del()=0;
	virtual void update()=0;
	bool animate = true;
	unsigned int index = 0;
};
template <class T>
class MeshObj : public _MeshObj {
public:
	~MeshObj() {  }
	void del() { delete (T*)this; }
	vec3 pos(int i=0) { return m->pos(i); };
	Mesh* m = NULL;
};

extern std::vector<Mesh*> MESH;
extern std::vector<unsigned int> _MESH;
extern std::vector<_MeshObj*> OBJS;
extern std::vector<unsigned int> _OBJS;
extern std::map<const char*, unsigned int> TEXS;

// Generates a mesh object
extern Mesh* create_mesh(
	std::vector<Vtx>& vtxs,
	std::vector<unsigned int>& inds,
	bool=true,
	unsigned int=GL_QUADS,
	unsigned int=GL_UNSIGNED_INT,
	unsigned int=0);

// Safely deletes a mesh, keeps track of empty mesh slots
extern void delete_mesh(Mesh*);

// Generates the meshobj wrapper for an object
extern void make_meshobj(_MeshObj*);

// Safely deletes a meshobj, keeps track of empty meshobj slots
extern void delete_meshobj(_MeshObj*);

// Generates an empty mesh
extern Mesh* blank_mesh(bool=true);

// Generates a square (0, 0, 0) -> (1, 1, 0), facing +Z, by default
extern Mesh* create_square(bool=true);

// Generates a plane of squares of the given dimensions with the default inner square dimensions
extern Mesh* create_plane(unsigned int=10, unsigned int=10);

// Generates a texture and attaches it to the provided mesh
extern void bind_texture(Mesh*, const char*);

// Changes how openGL will render the given mesh (GL_LINES, GL_TRIANGLES, etc.)
extern void change_rendering(Mesh*, unsigned int);

// Deallocates everything to do with mesh
extern void close_mesh();
