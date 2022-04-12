#include "Window.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

namespace window {
	void kernel() {
		glfwInit();
		GLFWwindow* w = glfwCreateWindow(640, 640, "", NULL, NULL);
		glewInit();
	};
};
