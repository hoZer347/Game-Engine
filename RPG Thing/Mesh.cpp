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
		glGenBuffers(1, &_vtxs);
		glBindBuffer(GL_ARRAY_BUFFER, _vtxs);

		glGenBuffers(1, &_inds);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

		stride = sizeof(GLfloat) * 3;
		shader = shader::create("Shaders/Lines");

		atbs.push_back(obj::new_attrib());
		glVertexAttribPointer(
			atbs.back(), 3,
			GL_FLOAT, GL_FALSE,
			stride,
			(void*)(0 * sizeof(GLfloat)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		GLint i;
		glGetProgramiv(shader, GL_VALIDATE_STATUS, &i);
		std::cout << i << std::endl;
		//glGetProgramiv(shader, GL_ATTACHED_SHADERS, &i);
		//std::cout << i << std::endl;
		//glGetProgramiv(shader, GL_ATTACHED_SHADERS, &i);
		//std::cout << i << std::endl;
	}
	void Lines::update() {
		glUniform4f(
			glGetUniformLocation(shader, "color"),
			color.x, color.y, color.z, color.w);
	}
	// Mesh::render()
	void Lines::draw() {
		glLineWidth(width);
		glDrawElements(GL_LINES, inds.size(), GL_UNSIGNED_INT, 0);
	}

	// Mesh::render()
	void Triangles::draw() {
		glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, 0);
	};

	// Mesh::render()
	void Quads::draw() {
		glDrawElements(GL_QUADS, inds.size(), GL_UNSIGNED_INT, 0);
	};
}
