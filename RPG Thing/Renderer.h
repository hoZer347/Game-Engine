#pragma once

#define GLM_FORCE_RADIANS
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "Inputs.h"
#include "Window.hpp"

#include <vector>
#include <iostream>
#include <fstream>

using namespace glm;

struct Camera {
	vec3
		up = vec3(0, 1, 0),
		eye = vec3(0, 0, 0),
		look = vec3(0, 0, -5);
	
	mat3
		cam_ray = mat3(0);

	mat4
		roll = mat4(1),
		ptch = mat4(1),
		yaww = mat4(1),
		trns = mat4(1),
		rotn = mat4(1),
		mode = mat4(1),
		norm = mat4(1),
		view = mat4(1),
		proj = mat4(1),
		mvp  = mat4(1);
};

class Renderer {
public:
	Renderer();
	~Renderer();
	void render(Mesh*);
	void update();
	void init();

	void create_shader(std::string, std::string);
	void create_shader(std::string, std::string, std::string);

	GLFWwindow* window = NULL;
	Camera* c = new Camera();

private:
	GLuint vao = 0;
	GLuint shader_programme = 0, depth_shader = 0;
	GLuint depth_map = 0;
	GLuint _vtxs = 0, _inds = 0;
	GLuint mode=0, norm=0, view=0, proj=0, mvp=0;

	int window_w = 640, window_h = 640;

	mat2x3 get_cam_ray();
};

static Renderer* create_renderer() {
	Renderer* r = new Renderer();
	
	return r;
}
