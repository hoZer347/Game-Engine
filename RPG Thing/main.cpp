// Memory Tracking
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <GLFW/glew.h>
#include <GLFW/glfw3.h>

#include "Spooler.h"
#include "Window.h"

#include <iostream>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto g = window::game::create();
	
	window::init(g);

	while (true) glfwPollEvents();

	return 0;
};
