#include "Renderer.h"

#include "Object.h"
#include "Inputs.h"
#include "Window.h"
#include "Camera.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace renderer {
	unsigned int
		fbo=0;

	void setup() {
		glfwInit();

		WINDOW = glfwCreateWindow(640, 640, "", NULL, NULL);
		glfwMakeContextCurrent(WINDOW);
		glfwSwapInterval(1);

		glewInit();

		glEnable(GL_TEXTURE_2D);

		glEnable(GL_MULTISAMPLE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_ALPHA_TEST);

		glClearColor(.1, .1, .1, 1);

		inputs::next();
		cam::create();
	};

	void close() {
		inputs::close();
		cam::close();
		glfwDestroyWindow(WINDOW);
		glfwTerminate();
	};

	void init() {
		while (!glfwWindowShouldClose(WINDOW)) {
			int w=0, h=0;
			glfwGetWindowSize(WINDOW, &w, &h);

			obj::update();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, w, h);
			obj::render();

			glfwSwapBuffers(WINDOW);
		}
	};
};
