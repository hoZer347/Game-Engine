#include "Inputs.h"

Inputs::Inputs(GLFWwindow* w, Room* r) {
	window = w;
	room = r;
}

void Inputs::update() {
	glfwPollEvents();

	_mx = -mx;
	_my = -my;
	glfwGetCursorPos(window, &mx, &my);
	_mx += mx;
	_my += my;

	_sx = -sx;
	_sy = -sy;
	glfwGetCursorPos(window, &sx, &sy);
	_sx += sx;
	_sy += sy;

	for (auto& i : listeners) {
		if (glfwGetKey(window, i.first))
			i.second(room);
		else if (glfwGetMouseButton(window, i.first))
			i.second(room);
		// TODO: add joystick functionality
	}
}
