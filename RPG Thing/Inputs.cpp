#include "Inputs.h"

Inputs* inputs = NULL;

Inputs::~Inputs() {
	for (auto& i : on_del)
		i();

	if (_prev)
		delete _prev;
}

void Inputs::update() {
	glfwPollEvents();
	
	double px=mx, py=my;

	glfwGetCursorPos(WINDOW, &mx, &my);

	dx = mx-px;
	dy = my-py;

	for (auto& i : f)
		i();
}

void init_inputs() {
	glfwSetMouseButtonCallback(
		WINDOW,
		[](GLFWwindow* w, int b, int a, int m) {
			if (inputs->m[b])
				inputs->m[b](a, m);
		});

	glfwSetKeyCallback(
		WINDOW,
		[](GLFWwindow* w, int k, int s, int a, int m) {
			if (inputs->k[k])
				inputs->k[k](s, a, m);
		});

	glfwSetScrollCallback(
		WINDOW,
		[](GLFWwindow* w, double x, double y) {
			inputs->s(x, y);
		});

	glfwSetCursorPosCallback(
		WINDOW,
		[](GLFWwindow* w, double x, double y) {
			inputs->c(x, y);
		});
}

void new_inputs() {
	if (!inputs) { inputs = new Inputs(); return; }

	Inputs* i = new Inputs;

	i->_prev = inputs;
	inputs = i;
}

void prev_inputs() {
	Inputs* i = inputs->_prev;
	inputs->_prev = NULL;
	delete inputs;

	inputs = i;
}
