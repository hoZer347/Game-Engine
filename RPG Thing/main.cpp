// Native Includes
#include "Object.h"
#include "Window.h"
#include "Renderer.h"

// Memory Tracking
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Testing Includes
#include "glm/glm.hpp"
#include <fstream>
#include <iostream>

using namespace glm;

GLuint create_shader(std::string f1, std::string f2) {
	std::ifstream _v(f1.c_str());
	std::string _vs((std::istreambuf_iterator<char>(_v)),
		std::istreambuf_iterator<char>());

	std::ifstream _f(f2.c_str());
	std::string _fs((std::istreambuf_iterator<char>(_f)),
		std::istreambuf_iterator<char>());

	const char* vertex_shader = _vs.c_str();
	const char* fragment_shader = _fs.c_str();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glUseProgram(shader_programme);

	return shader_programme;
}

struct Mesh {
	float vtxs[12] = {
		-0.5, -0.5, 0,
		 0.5, -0.5, 0,
		 0.5,  0.5, 0,
		-0.5,  0.5, 0,
	};
};

class O : public Object::Obj<O> {
public:
	~O() {
		delete m;
		glDeleteProgram(shader_programme);
		glDeleteBuffers(1, &_vtxs);
	}
	void setup() {
		glGenBuffers(1, &_vtxs);

		shader_programme = create_shader("Shaders/default.vert", "Shaders/default.frag");
	};
	void update() {}
	void render() {
		glBindBuffer(GL_ARRAY_BUFFER, _vtxs);

		glVertexAttribPointer(
			0, 3,
			GL_FLOAT, GL_FALSE,
			3 * sizeof(float),
			(void*)0);
		glEnableVertexAttribArray(0);

		glBufferData(
			GL_ARRAY_BUFFER,
			12 * sizeof(float),
			m->vtxs,
			GL_DYNAMIC_DRAW);

		// Drawing
		glDrawArrays(GL_QUADS, 0, 12);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	};

	Mesh* m = NULL;

private:
	GLuint _vtxs = 0, shader_programme = 0;
	int i = 0;
};

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	O* o = new O();
	Mesh* m = new Mesh();
	o->m = m;

	Renderer::run();

	return 0;
}
