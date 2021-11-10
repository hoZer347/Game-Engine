#pragma once

#include "Room.h"
#include "Timer.h"

class Game {
public:
	Game(Room* r) { room = r; };
	void init();

	Room* room = NULL;
};

// Does Nothing (Used to "delete" functionality)
static auto null = [](Room*){
	
};

// WASD THINGS

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

// MOUSE THINGS

// SCROLL THINGS

static auto ScrollFunc = [](GLFWwindow* w, double x, double y) {
	Room* r = (Room*)glfwGetWindowUserPointer(w);
	Camera* c = r->r->c;
	
	r->r->c->trns = translate(r->r->c->trns, vec3(vec4(0, 0, y, 1) * r->r->c->rotn));
};

static auto scroll_zooms_camera = [](Room* r) {
	glfwSetScrollCallback(r->r->window, ScrollFunc);
};

// RAYS AND STUFF

enum {
	EYE = 0,
	RAY = 1,
	LOOK = 2
};

static auto get_cam_ray = [](Room* r, std::function<void(Vtx&)> func = default_func) {
	int w = 0, h = 0;
	glfwGetWindowSize(r->r->window, &w, &h);

	vec4 mv = vec4((r->i->mx - w / 2) / (w / 2), (-r->i->my + h / 2) / (h / 2), 0, 1);

	Vtx v;

	vec4 eye = mv + vec4(r->r->c->eye, 0);
		 eye = inverse(r->r->c->mvp) * eye;
		 eye /= eye.w;
		 v.pos = vec3(eye);
		 func(v);
		 eye = vec4(v.pos, 1);

	vec4 look = mv + vec4(r->r->c->look, 0);
		 look = inverse(r->r->c->mvp) * look;
		 look /= look.w;
		 v.pos = vec3(look);
		 func(v);
		 look = vec4(v.pos, 1);

	vec4 ray = (look - eye);
		 ray = normalize(ray);

	mat3 ret = { vec3(eye), vec3(ray), vec3(look) };

	return ret;
};
