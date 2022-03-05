#include "Mesh.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include "Shaders.h"
#include "Textures.h"

#include <iostream>

namespace mesh {
	void Mesh::pump(std::vector<float>& V) {
		for (auto& v : V)
			vtxs.push_back(v);
	};
	void Mesh::pump(std::vector<unsigned int>& I) {
		for (auto& i : I)
			inds.push_back(i);
	};
	void Mesh::add_attrib(unsigned char size) {
		atbs.push_back({ atbs.size(), size});
		stride += size;
	};
	void Mesh::setup() {
		glGenBuffers(1, &_vtxs);
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



	Shader::~Shader() {
		glDeleteShader(shader);
	};
	void Shader::set_shader(const char* file_name) {
		shader_name = file_name;
	};
	void Shader::setup() {
		shader = shader::create(shader_name);
		glUseProgram(shader);
		Mesh::setup();
	};
	void Shader::render() {
		glUseProgram(shader);
		Mesh::render();
	};



	Texture::~Texture() {
		glDeleteTextures(1, &texture);
	}
	void Texture::setup() {
		Shader::setup();
		texture = texture::create(texture_name);
	}
	void Texture::set_texture(const char* file_name) {
		texture_name = file_name;
	};
	void Texture::render() {
		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(shader);
		glUniform1i(glGetUniformLocation(shader, "tex"), 0);
		Shader::Mesh::render();
		glBindTexture(GL_TEXTURE_2D, 0);
	};



	vec4 Transform::pos(unsigned int i) {
		return vec4(vtxs[i+0], vtxs[i+1], vtxs[i+2], 1) * trns;
	};
}
