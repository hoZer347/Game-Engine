#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Inputs {
public:
	Inputs(GLFWwindow*);
	void update();

	GLFWwindow* window = NULL;
	double mx=0, my=0, dx=0, dy=0;
};

extern Inputs* inputs;
