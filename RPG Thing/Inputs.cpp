#include "Inputs.h"

Inputs* inputs = NULL;

void Inputs::next() {
	Inputs* i = inputs;
	inputs = _next;
	inputs = new Inputs();
	inputs->window = i->window;

	if (inputs) inputs->_prev = i;
}

void Inputs::prev() {
	Inputs* i = inputs;
	inputs = _prev;

	if (inputs) inputs->_next = i;
}

void Inputs::update() {
	glfwPollEvents();
	
	double px=mx, py=my;

	glfwGetCursorPos(window, &mx, &my);

	dx = mx-px;
	dy = my-py;

	for (auto& i : f)
		if (glfwGetKey(window, i.first))
			i.second();
		else if (glfwGetMouseButton(window, i.first))
			i.second();
}
