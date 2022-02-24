#include "Renderer.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Object.h"

namespace renderer {
	void setup() {
		
		glfwInit();

		WINDOW = glfwCreateWindow(640, 640, "", NULL, NULL);
		glfwMakeContextCurrent(WINDOW);

		glewInit();

		glClearColor(0.5, 0.5, 0.5, 1);

		obj::setup();
	};
	
	bool update() {
		glfwPollEvents();

		int window_w, window_h;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetWindowSize(WINDOW, &window_w, &window_h);
		glViewport(0, 0, window_w, window_h);

		obj::update();

		return !glfwWindowShouldClose(WINDOW);
	};
	
	void render() {
		obj::render();

		glfwSwapBuffers(WINDOW);
	};

	void end() {
		obj::clear();
		glfwDestroyWindow(WINDOW);
		glfwTerminate();
	};

	void init() {
		setup();

		while (update()) render();

		end();
	};
}
