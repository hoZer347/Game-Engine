#include "Renderer.h"

#include "Object.h"
#include "Inputs.h"
#include "Window.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

namespace renderer {
	bool end = false;

	void setup() {
		glfwInit();
		WINDOW = glfwCreateWindow(640, 640, "", NULL, NULL);
		glfwMakeContextCurrent(WINDOW);
		glewExperimental = GL_TRUE;
		glfwSwapInterval(1);
		glewInit();

		glEnable(GL_TEXTURE_2D);
		
		glEnable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_ALPHA_TEST);

		obj::setup();

		glClearColor(0.5, 0.5, 0.5, 1); // RMV
	}

	void close() {
		glfwDestroyWindow(WINDOW);
		glfwTerminate();
	}

	void init() {
		setup();

		while (!glfwWindowShouldClose(WINDOW)) {
			int w, h;
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwGetWindowSize(WINDOW, &w, &h);
			glViewport(0, 0, w, h);

			obj::update();
			obj::render();

			glfwSwapBuffers(WINDOW);
		}

		inputs::close();
		close();
	}
};
