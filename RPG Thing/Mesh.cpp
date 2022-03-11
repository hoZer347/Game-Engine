#include "Mesh.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include "Shaders.h"

#include <iostream>

namespace mesh {
	unsigned int
		_vtxs=0,
		_inds=0;

	Mesh::~Mesh() {
		glDeleteShader(shader);
	}
	void Mesh::add_attrib(unsigned char size) {
		atbs.push_back({ atbs.size(), size });
		stride += size;
	};
	void Mesh::set_shader(const char* file_name) {
		shader = shader::create(file_name);
	};
	vec4 Mesh::pos(unsigned int i) {
		return vec4(vtxs[0], vtxs[1], vtxs[2], 1) * trns;
	};
	void Mesh::pump(std::vector<float>& V) {
		for (auto& v : V)
			vtxs.push_back(v);
	};
	void Mesh::pump(std::vector<unsigned int>& I) {
		for (auto& i : I)
			inds.push_back(i);
	};
	void Mesh::setup() {
		glUseProgram(shader);

		if (!_vtxs)
			glGenBuffers(1, &_vtxs);
		if (!_inds)
			glGenBuffers(1, &_inds);

		glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

		unsigned int i=0;
		for (auto& a : atbs) {
			glVertexAttribPointer(
				a.first, a.second,
				GL_FLOAT, GL_FALSE,
				stride * sizeof(float),
				(void*) (i * sizeof(float)));
			i += a.second;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};
	void Mesh::update() {

	};
	void Mesh::render() {
		glUseProgram(shader);

		glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

		for (auto& a : atbs)
			glEnableVertexAttribArray(a.first);

		glBufferData(
			GL_ARRAY_BUFFER,
			vtxs.size() * sizeof(float),
			vtxs.data(),
			GL_DYNAMIC_DRAW);

		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			inds.size() * sizeof(unsigned int),
			inds.data(),
			GL_DYNAMIC_DRAW);

		glDrawElements(drawing_mode, inds.size(), GL_UNSIGNED_INT, 0);

		for (auto& a : atbs)
			glDisableVertexAttribArray(a.first);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};
};
