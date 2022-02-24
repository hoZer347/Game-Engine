#include "Mesh.h"

#include "Object.h"
#include "Shader.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
using namespace glm;

#include <vector>
#include <iostream>

namespace mesh {
	Mesh::~Mesh() {
		glDeleteProgram(shader);
		glDeleteBuffers(1, &_vtxs);
		glDeleteBuffers(1, &_inds);
	}
	void Mesh::add_attrib(unsigned char size) {
		glGenBuffers(1, &_vtxs);
		glBindBuffer(GL_ARRAY_BUFFER, _vtxs);

		glGenBuffers(1, &_inds);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

		stride += sizeof(GLfloat) * size;

		atbs.push_back(obj::new_attrib());
		glVertexAttribPointer(
			atbs.back(), size,
			GL_FLOAT, GL_FALSE, 0,
			(void*)(0 * sizeof(GLfloat)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Mesh::pump(std::vector<float>& V, unsigned int s) {
		vtxs.insert(vtxs.end(), V.begin(), V.end());
	};
	void Mesh::pump(std::vector<unsigned int>& V, unsigned int s) {
		inds.insert(inds.end(), V.begin(), V.end());
	};
	void Mesh::setup() {

	}
	void Mesh::update() {

	}
	void Mesh::render() {
		glUseProgram(shader);

		for (auto& a : atbs)
			glEnableVertexAttribArray(a);

		glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
		glBufferData(
			GL_ARRAY_BUFFER,
			vtxs.size() * sizeof(GLfloat),
			vtxs.data(),
			GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			inds.size() * sizeof(GLuint),
			inds.data(),
			GL_DYNAMIC_DRAW);

		draw();

		for (auto& a : atbs)
			glDisableVertexAttribArray(a);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Lines::setup() {
		add_attrib(3);
		shader = shader::create("Shaders/Lines");
	}
	void Lines::update() {
		glUniform4f(
			glGetUniformLocation(shader, "color"),
			color.x, color.y, color.z, color.w);
	}
	void Lines::draw() {
		glLineWidth(width);
		glDrawElements(GL_LINES, inds.size(), GL_UNSIGNED_INT, 0);
	}

	void Triangles::draw() {
		glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, 0);
	};

	void Quads::draw() {
		glDrawElements(GL_QUADS, inds.size(), GL_UNSIGNED_INT, 0);
	};
}
