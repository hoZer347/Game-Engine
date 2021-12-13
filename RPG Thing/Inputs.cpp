#include "Inputs.h"

Inputs::Inputs(GLFWwindow* w) {
	window = w;
}

void Inputs::update() {
	glfwPollEvents();
}

Inputs* inputs;
