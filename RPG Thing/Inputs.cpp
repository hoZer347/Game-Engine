#include "Inputs.h"

Inputs inputs;

void Inputs::update() {
	glfwPollEvents();

	double px=mx, py=my;

	glfwGetCursorPos(window, &mx, &my);

	dx = mx-px;
	dy = my-py;

	for (auto& i : f)
		if (glfwGetKey(window, i.first))
			i.second->f(i.second);
}
