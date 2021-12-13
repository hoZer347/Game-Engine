#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>
#include <functional>

class Inputs {
public:
	Inputs(GLFWwindow*);
	void update();

	GLFWwindow* window = NULL;
};

extern Inputs* inputs;
