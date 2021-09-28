#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderable.h"

#include <iostream>
#include <fstream>

using namespace glm;

enum {
	VTX_POS = 0,
	VTX_CLR = 1,
	TEX_POS = 2,
	TEX_CDS = 3,
};

class Renderer {
public:
	Renderer();

	void load();
	void update();

	void add(Vtx v) { vtxs.push_back(v);
	glBufferData(GL_ARRAY_BUFFER, vtxs.size() * sizeof(Vtx), vtxs.data(), GL_STATIC_DRAW); };

	GLFWwindow* window = NULL;

	uint shader_programme=0;
	uint vao=0, vbo=0;

private:
	std::vector<Vtx> vtxs;
	std::vector<Tex> texs;

	mat4
		tran = mat4(1.0f),
		rotn = mat4(1.0f),
		scal = mat4(1.0f),
		mode = mat4(1.0f), // Tran * Rotn * Scal
		view = mat4(1.0f),
		proj = mat4(1.0f),
		mvp = mat4(1.0f);
};
