#include "Inputs.h"

Inputs::Inputs(GLFWwindow* w) {
	window = w;
}

void Inputs::update() {
	output.clear();

	for (auto& i : listeners)
		if (glfwGetKey(window, i.first))
			output.push_back(i.second);
}
