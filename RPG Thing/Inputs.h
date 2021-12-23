#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <vector>
#include <map>

struct Input {
	std::function<void(Input*)> f;
	std::vector<void*> mem;
};

class Inputs {
public:
	void update();
	auto& operator[](short i) { return f[i]; }

	GLFWwindow* window = NULL;
	double mx=0, my=0, dx=0, dy=0;
	std::map<short, Input*> f;
};

extern Inputs inputs;
