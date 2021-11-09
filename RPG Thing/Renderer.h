#pragma once

#define GLM_FORCE_RADIANS
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL/SOIL.h"

#include "Renderable.h"

#include <vector>
#include <iostream>
#include <fstream>

using namespace glm;

struct Camera {
	vec3
		up = vec3(0, 1, 0),
		eye = vec3(0, 0, 0),
		look = vec3(0, 0, -5);

	mat4
		roll = mat4(1.0f), // X axis
		ptch = mat4(1.0f), // Y axis
		yaww = mat4(1.0f), // Z axis
		trns = mat4(1.0f),
		rotn = mat4(1.0f),
		mode = mat4(1.0f),
		norm = mat4(1.0f),
		view = mat4(1.0f),
		proj = mat4(1.0f),
		mvp  = mat4(1.0f);
};

class Renderer {
public:
	Renderer();

	void load();
	void update();

	void create_shader(std::string, std::string);
	void create_shader(std::string, std::string, std::string);

	GLFWwindow* window = NULL;
	Camera* c = new Camera();
	
	GLuint vao=0;
	GLuint shader_programme=0, depth_shader=0;
	GLuint depth_map=0;
	GLuint _vtxs=0, _inds=0;

	int window_w=640, window_h=640;
};
