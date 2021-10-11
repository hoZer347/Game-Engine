#pragma once

#define GLM_FORCE_RADIANS
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderable.h"
#include "SOIL/SOIL.h"

#include <iostream>
#include <fstream>

using namespace glm;

struct Camera {
	vec3
		up = vec3(0, 1, 0);

	mat4
		mode = mat4(1.0f),
		norm = mat4(1.0f),
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

	void create_shader(std::string, std::string);
	void create_shader(std::string, std::string, std::string);
	void add(GLuint i) { inds.push_back(i); };
	void add(std::string);
	void add(Vtx v) { vtxs.push_back(v); };

	GLFWwindow* window = NULL;

	GLuint vao=0;
	GLuint shader_programme=0, depth_shader=0;
	GLuint depth_map=0;
	GLuint _inds=0, _vtxs=0;

	std::vector<Vtx> vtxs;
	std::vector<Vtx> texs;
	std::vector<GLuint> inds;
	std::vector<GLuint> tnds;

	GLuint texture=0, texID=0, num_texs=0;

	int window_w=640, window_h=640;

	Camera c;
};
