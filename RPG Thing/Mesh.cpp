#include "Mesh.h"

#include <GLFW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace mesh {
	Mesh::Mesh() {
		glGenBuffers(1, &fbo);
		glGenBuffers(1, &ebo);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
		glEnableVertexAttribArray(0);
	};
	Mesh::~Mesh() {
		glDeleteBuffers(1, &fbo);
		glDeleteBuffers(1, &ebo);
	};
	void Mesh::stage(unsigned char& stg) {
		
	};
	void Mesh::update_buffers() {
		glUseProgram(shader);

		glBindBuffer(GL_ARRAY_BUFFER, fbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		glBufferData(
			GL_ARRAY_BUFFER,
			data.size() * sizeof(float),
			data.data(),
			GL_DYNAMIC_DRAW);

		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			inds.size() * sizeof(unsigned int),
			inds.data(),
			GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};
	void Mesh::pump(std::vector<float>& v) {
		data.insert(data.end(), v.begin(), v.end());
		update_buffers();
	};
	void Mesh::pump(std::vector<unsigned int>& v) {
		inds.insert(inds.end(), v.begin(), v.end());
		update_buffers();
	};
	void Mesh::stg_update() {

	};
	void Mesh::stg_render() {
		glUseProgram(shader);

		glBindBuffer(GL_ARRAY_BUFFER, fbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		for (auto& t : texs)
			glBindTexture(GL_TEXTURE_2D, t);

		glDrawElements(gl_render_type, inds.size(), GL_UNSIGNED_INT, NULL);
		
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};

	void create() {
		mesh::Mesh();
	};
};
