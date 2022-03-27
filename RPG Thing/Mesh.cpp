#include "Mesh.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include "Shaders.h"
#include "Textures.h"

#include <iostream>

namespace mesh {
	std::vector<Mesh*> MESH;

	unsigned int
		atb_index=0;

	Mesh::Mesh() {
		MESH.push_back(this);

		if (!_vtxs)
			glGenBuffers(1, &_vtxs);
		if (!_inds)
			glGenBuffers(1, &_inds);
	};
	Mesh::~Mesh() {
		glDeleteShader(shader);
	};
	void Mesh::add_attrib(unsigned char size) {
		atbs.push_back({ atb_index++, size });
		stride += size;
	};
	void Mesh::add_texture(const char* file_name) {
		texs.push_back(texture::create(file_name));
	}
	void Mesh::add_texture(unsigned int t) {
		texs.push_back(t);
	};
	void Mesh::set_shader(const char* file_name) {
		shader = shader::create(file_name);
	};
	void Mesh::set_shader(
		const char* file_name1,
		const char* file_name2) {
		shader = shader::create(file_name1, file_name2);
	};
	void Mesh::set_shader(
		const char* file_name1,
		const char* file_name2,
		const char* file_name3) {
		shader = shader::create(file_name1, file_name2, file_name3);
	};
	void Mesh::set_shader(unsigned int s) {
		shader = s;
	};
	vec4 Mesh::pos(unsigned int i) {
		return vec4(vtxs[0], vtxs[1], vtxs[2], 1) * trns;
	};
	void Mesh::setup() {
		glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

		unsigned int i=0;
		for (auto& a : atbs) {
			glVertexAttribPointer(
				a.first, a.second,
				GL_FLOAT, GL_FALSE,
				stride * sizeof(float),
				(void*)(i * sizeof(float)));
			i += a.second;
			glEnableVertexAttribArray(a.first);
		};
		
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

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};
	void Mesh::update() {
		glUniformMatrix4fv(glGetUniformLocation(shader, "trns"),
		1, GL_FALSE, &trns[0][0]);
	};
	void Mesh::render() {
		glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

		for (unsigned int i = 0; i < texs.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, texs[i]);
		};

		glDrawElements(drawing_mode, inds.size(), GL_UNSIGNED_INT, 0);

		for (unsigned int i = 0; i < texs.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		};

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};

	mat4& trns(void* m) {
		return ((Mesh*)m)->trns;
	};
};
