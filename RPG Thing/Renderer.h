#pragma once

#define GLM_FORCE_RADIANS
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL/SOIL.h"

#include "Mesh.h"
#include "Inputs.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

using namespace glm;

struct Camera {
	vec3
		up = vec3(0, 1, 0),
		eye = vec3(0, 0, 0),
		look = vec3(0, 0, -5);
	
	mat3
		cam_ray = mat3(0);

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
	void render(Mesh*);
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

extern Renderer* renderer;

static std::function<void()> load_game;

static auto start_renderer() {
	auto update = []() {
		renderer = new Renderer();
		inputs = new Inputs(renderer->window);

		load_game();

		while (!glfwWindowShouldClose(renderer->window)) {
			inputs->update();

			for (auto& m : OBJS)
				if (m->animate)
					m->update();
			
			renderer->update();
		}
	};

	std::thread render (update);

	return render;
}

/*

static auto free_camera = [](Room* r) {
	(*r->i)[GLFW_KEY_W] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(0, 0, .1, 1) * r->r->c->rotn)); };
	(*r->i)[GLFW_KEY_A] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(.1, 0, 0, 1) * r->r->c->rotn)); };
	(*r->i)[GLFW_KEY_S] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(0, 0, -.1, 1) * r->r->c->rotn)); };
	(*r->i)[GLFW_KEY_D] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(-.1, 0, 0, 1) * r->r->c->rotn)); };
	(*r->i)[GLFW_KEY_SPACE] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(0, -.1, 0, 1) * r->r->c->rotn)); };
	(*r->i)[GLFW_KEY_LEFT_CONTROL] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(0, .1, 0, 1) * r->r->c->rotn)); };

	(*r->i)[GLFW_MOUSE_BUTTON_RIGHT] = [](Room* r) {
		r->r->c->yaww = rotate(r->r->c->yaww, (float)r->i->_mx / 100, vec3(0, 1, 0));
		r->r->c->ptch = rotate(r->r->c->ptch, (float)r->i->_my / 100, vec3(vec4(1, 0, 0, 1) * r->r->c->roll * r->r->c->ptch));
	};
};

static auto ScrollFunc = [](GLFWwindow* w, double x, double y) {
	Room* r = (Room*)glfwGetWindowUserPointer(w);
	Camera* c = r->r->c;

	r->r->c->trns = translate(r->r->c->trns, vec3(vec4(0, 0, y, 1) * r->r->c->rotn));
};

static auto scroll_zooms_camera = [](Room* r) {
	glfwSetScrollCallback(r->r->window, ScrollFunc);
};

enum {
	EYE = 0,
	RAY = 1,
	LOOK = 2
};

static auto get_cam_ray = [](Room* r) {
	if (!r)
		return mat3(0);

	int w = 0, h = 0;
	glfwGetWindowSize(r->r->window, &w, &h);

	vec4 mv = vec4((r->i->mx - w / 2) / (w / 2), (-r->i->my + h / 2) / (h / 2), 0, 1);

	Vtx v;

	vec4 eye = mv + vec4(r->r->c->eye, 0);
	eye = inverse(r->r->c->mvp) * eye;
	eye /= eye.w;
	v.pos = vec3(eye);
	eye = vec4(v.pos, 1);

	vec4 look = mv + vec4(r->r->c->look, 0);
	look = inverse(r->r->c->mvp) * look;
	look /= look.w;
	v.pos = vec3(look);
	look = vec4(v.pos, 1);

	vec4 ray = (look - eye);
	ray = normalize(ray);

	mat3 ret = { vec3(eye), vec3(ray), vec3(look) };

	return ret;
};

*/
