#include "Inputs.h"

Inputs::Inputs(GLFWwindow* w) {
	window = w;
}

void Inputs::update() {
	glfwPollEvents();

	double px=mx, py=my;

	glfwGetCursorPos(window, &mx, &my);

	dx = mx-px;
	dy = my-py;
}

Inputs* inputs;
