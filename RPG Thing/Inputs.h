#pragma once

#include <glm/glm.hpp>

#include "Window.hpp"

#include <functional>
#include <vector>
#include <map>

#include <iostream>

using namespace glm;

enum {
	CAM_EYE=0,
	CAM_RAY=1
};

class Inputs {
public:
	~Inputs();
	void update();

	GLFWwindow* window = WINDOW;
	double
		mx=0, my=0, // Current mouse pos
		dx=0, dy=0; // Delta mouse pos
	
	// Memory for inputs to use
	std::map<const char*, void*> mem;
	
	// Every-tick inputs for mouse and keyboard
	std::map<short, std::function<void()>> f;

	// Window keyboard inputs
	std::map<short, std::function<void(int, int, int)>> k;
	
	// Window mouse inputs
	std::map<short, std::function<void(int, int)>> m;
	
	// Cursor movement
	std::function<void(double, double)> c = [](double, double) {};
	
	// Scroll input
	std::function<void(double, double)> s = [](double, double) {};

	// Updated through renderer
	mat2x3 mouse_ray = mat2x3(1);

	// Linked list implementation for scene hierarchy
	void next();
	void prev();
private:
	Inputs* _next = NULL;
	Inputs* _prev = NULL;
};

extern Inputs* inputs;

static void init_inputs(GLFWwindow* w) {
	inputs = new Inputs();
	inputs->window = w;

	glfwSetMouseButtonCallback(
		inputs->window,
		[](GLFWwindow* w, int b, int a, int m) {
			if (inputs->m[b])
				inputs->m[b](a, m);
		});

	glfwSetKeyCallback(
		inputs->window,
		[](GLFWwindow* w, int k, int s, int a, int m) {
			if (inputs->k[k])
				inputs->k[k](s, a, m);
		});
	
	glfwSetScrollCallback(
		inputs->window,
		[](GLFWwindow* w, double x, double y) {
			inputs->s(x, y);
		});

	glfwSetCursorPosCallback(
		inputs->window,
		[](GLFWwindow* w, double x, double y) {
			inputs->c(x, y);
		});
}
