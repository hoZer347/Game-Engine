#include "Renderer.h"

#include "Object.h"
#include "Inputs.h"
#include "Window.h"
#include "Camera.h"
#include "Lighting.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace renderer {
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

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_ALPHA_TEST);

		glEnable(GL_CULL_FACE);

		inputs::next();

		glClearColor(0.5, 0.5, 0.5, 1); // RMV
	};

	void close() {
		lighting::close();
		inputs::close();
		glfwDestroyWindow(WINDOW);
		glfwTerminate();
	};

	void init() {
		obj::setup();

		while (!glfwWindowShouldClose(WINDOW)) {
			int w=0, h=0;
			glfwGetWindowSize(WINDOW, &w, &h);

			cam::update();
			obj::update();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, w, h);
			obj::render();

			glfwSwapBuffers(WINDOW);
		}

		close();
	};
};
