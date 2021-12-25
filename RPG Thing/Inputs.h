#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <vector>
#include <map>

#include <iostream>

class Inputs {
public:
	void update();

	GLFWwindow* window = NULL;
	double mx=0, my=0, dx=0, dy=0;
	
	std::map<const char*, void*> mem;
	std::map<short, std::function<void()>> f;
	std::map<short, std::function<void(int, int, int)>> k;
	std::map<short, std::function<void(int, int)>> m;
};

extern Inputs inputs;

static void init_inputs(GLFWwindow* w) {
	inputs.window = w;

	glfwSetMouseButtonCallback(
		inputs.window,
		[](GLFWwindow* w, int b, int a, int m) {
			if (inputs.m[b])
				inputs.m[b](a, m);
		});

	glfwSetKeyCallback(
		inputs.window,
		[](GLFWwindow* w, int k, int s, int a, int m) {
			if (inputs.k[k])
				inputs.k[k](s, a, m);
		});
}
