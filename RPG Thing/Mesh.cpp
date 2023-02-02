#include "Mesh.h"

#include <glm/gtx/transform.hpp>

std::vector<Mesh*> MESH;
std::vector<unsigned int> _MESH;
std::vector<_MeshObj*> OBJS;
std::vector<unsigned int> _OBJS;
std::map<const char*, unsigned int> TEXS;

Mesh* create_mesh(
	std::vector<Vtx>& vtxs,
	std::vector<unsigned int>& inds,
	bool add,
	unsigned int gl_render_type,
	unsigned int gl_data_type,
	unsigned int gl_texture) {

	Mesh* m = new Mesh();

	for (auto& i : vtxs)
		m->vtxs.push_back(i);

	for (auto& i : inds)
		m->inds.push_back(i);

	m->gl_render_type = gl_render_type;
	m->gl_data_type = gl_data_type;
	m->gl_texture = gl_texture;

	if (add) {
		if (!_MESH.empty()) {
			MESH[_MESH.back()] = m;
			m->index = _MESH.back();
			_MESH.pop_back();
		}
		else {
			m->index = MESH.size();
			MESH.push_back(m);
		}
	}

	return m;
}

void delete_mesh(Mesh* m) {
	if (!m) return;

	_MESH.push_back(m->index);

	MESH[m->index] = NULL;

	delete m;
}

void make_meshobj(_MeshObj* m) {
	if (!_OBJS.empty()) {
		OBJS[_OBJS.back()] = m;
		m->index = _OBJS.back();
		_OBJS.pop_back();
	}
	else {
		m->index = OBJS.size();
		OBJS.push_back(m);
	}
}

void delete_meshobj(_MeshObj* m) {
	if (!m) return;

	_OBJS.push_back(m->index);

	OBJS[m->index] = NULL;

	m->del();
}

Mesh* blank_mesh(bool add) {
	Mesh* m = new Mesh();

	if (add) {
		if (!_MESH.empty()) {
			MESH[_MESH.back()] = m;
			m->index = _MESH.back();
			_MESH.pop_back();
		}
		else {
			m->index = MESH.size();
			MESH.push_back(m);
		}
	}

	return m;
}

Mesh* create_square(bool add) {
	std::vector<Vtx> vtxs = { Vtx(), Vtx(), Vtx(), Vtx() };

	vtxs[0] = Vtx({ vec3(0, 0, 0), vec4(1), vec3(0, 0, 1), vec2(0, 0) });
	vtxs[1] = Vtx({ vec3(1, 0, 0), vec4(1), vec3(0, 0, 1), vec2(1, 0) });
	vtxs[2] = Vtx({ vec3(1, 1, 0), vec4(1), vec3(0, 0, 1), vec2(1, 1) });
	vtxs[3] = Vtx({ vec3(0, 1, 0), vec4(1), vec3(0, 0, 1), vec2(0, 1) });

	std::vector<unsigned int> inds = { 0, 1, 2, 3 };

	return create_mesh(vtxs, inds, add);
}

Mesh* create_plane(unsigned int x, unsigned int y) {
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

void bind_texture(Mesh* m, const char* file_name) {
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

void change_rendering(Mesh* m, unsigned int gl_render_type) {
	if (m->gl_render_type == gl_render_type)
		return;

	std::vector<unsigned int> new_inds;

	unsigned int index = 0;

	switch (m->gl_render_type) {

	case GL_QUADS:
		switch (gl_render_type) {
		case GL_LINES:
			for (unsigned int i = 0; i < m->inds.size(); i += 4) {
				new_inds.push_back(m->inds[index++]);
				new_inds.push_back(m->inds[index]);
				new_inds.push_back(m->inds[index++]);
				new_inds.push_back(m->inds[index]);
				new_inds.push_back(m->inds[index++]);
				new_inds.push_back(m->inds[index]);
				new_inds.push_back(m->inds[index++]);
				new_inds.push_back(m->inds[index - 4]);
			}
			break;
		default:
			break;
		}
		break;

	case GL_LINES:
		switch (gl_render_type) {
		case GL_QUADS:
			for (unsigned int i = 0; i < m->inds.size(); i += 2)
				new_inds.push_back(m->inds[i]);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	m->inds = new_inds;
	m->gl_render_type = gl_render_type;
}

void close_mesh() {
	for (auto& m : MESH)
		if (m)
			delete m;

	for (auto& o : OBJS)
		if (o)
			o->del();

	for (auto& i : TEXS)
		glDeleteTextures(1, &i.second);
}
