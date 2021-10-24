#pragma once

#include "Grid.h"
#include "Renderer.h"
#include "Room.h"

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

static auto wasd_strafes_camera = [](Room* r) {
	(*r->i)[GLFW_KEY_W] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(  0,   0,  .1, 1) * r->r->c->rotn)); };
	(*r->i)[GLFW_KEY_A] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4( .1,   0,   0, 1) * r->r->c->rotn)); };
	(*r->i)[GLFW_KEY_S] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(  0,   0, -.1, 1) * r->r->c->rotn)); };
	(*r->i)[GLFW_KEY_D] = [](Room* r) { r->r->c->trns = translate(r->r->c->trns, vec3(vec4(-.1,   0,   0, 1) * r->r->c->rotn)); };
};
static auto wasd_do_nothing = [](Room* r) {
	(*r->i).rmv(GLFW_KEY_W);
	(*r->i).rmv(GLFW_KEY_A);
	(*r->i).rmv(GLFW_KEY_S);
	(*r->i).rmv(GLFW_KEY_D);
};

// MOUSE THINGS

static auto mouse_rotates_camera = [](Room* r) {
	(*r->i)[GLFW_MOUSE_BUTTON_LEFT] = [](Room* r) {
		r->r->c->ptch = rotate(r->r->c->ptch, (float)r->i->_my / 100, vec3(vec4(1, 0, 0, 1) * r->r->c->rotn));
	};

	(*r->i)[GLFW_MOUSE_BUTTON_RIGHT] = [](Room* r) { 
		r->r->c->yaww = rotate(r->r->c->yaww, (float)r->i->_mx / 100, vec3(0, 1, 0));
	};
};

// SCROLL THINGS

static auto ScrollFunc = [](GLFWwindow* w, double x, double y) {
	Room* r = (Room*)glfwGetWindowUserPointer(w);
	Camera* c = r->r->c;

	c->eye += vec3(0, -y, -y);
};

static auto scroll_zooms_camera = [](Room* r) {
	glfwSetScrollCallback(r->r->window, ScrollFunc);
};
