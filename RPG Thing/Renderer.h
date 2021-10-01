#pragma once

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderable.h"

#include <iostream>
#include <fstream>

using namespace glm;

struct Camera {
	vec3
		up = vec3(0, 1, 0);

	mat4
		mode = mat4(1.0f),
		view = mat4(1.0f),
		proj = mat4(1.0f),
		mvp = mat4(1.0f);
};

class Renderer {
public:
	Renderer();

	void load();
	void update();

	Camera* get_cam() { return &c; };

	void add(Vtx v) { vtxs.push_back(v);
	glBufferData(GL_ARRAY_BUFFER, vtxs.size() * sizeof(Vtx), vtxs.data(), GL_STATIC_DRAW); };

	GLFWwindow* window = NULL;

	uint shader_programme=0;
	uint vao=0, vbo=0;

private:
	std::vector<Vtx> vtxs;
	std::vector<Tex> texs;

	int window_w=640, window_h=640;

	Camera c;
};
