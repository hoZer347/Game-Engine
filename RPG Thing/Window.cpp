#include "Window.h"

// GL imports
#include <GLFW/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include "Spooler.h"

#include <vector>

namespace window  {
	std::vector<GLFWwindow*> WINDOWS;
	 
	void* create(int x, int y, const char* name) {
		glfwInit();
		GLFWwindow* w = glfwCreateWindow(x, y, name, NULL, NULL);
		glewInit();
		WINDOWS.push_back(w);

		return w;
	};

	extern void init_openGL() {

	};
};
