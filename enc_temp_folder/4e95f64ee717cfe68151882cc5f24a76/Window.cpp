#include "Window.h"

#include <GLFW/glew.h>
#include <GLFW/glfw3.h>

#include "Object.h"
#include "Spooler.h"

#include <iostream>

namespace window {
	const unsigned char STG_RENDER = 1;

	struct Window : spooler::thread<std::vector<obj::Obj*>> {
		Window() {
			obj = &obj::OBJS;
			_t = std::thread(manage, this);
		};
		~Window() {
			glfwDestroyWindow(w);
			glfwTerminate();
		};
		void render() {
			PAUSE = false;

			while (!PAUSE);
		};
		static void manage(Window* w) {
			glfwInit();
			w->w = glfwCreateWindow(640, 640, "", NULL, NULL);
			glfwMakeContextCurrent(w->w);
			glfwSwapInterval(0);
			glewExperimental = true;
			glClearColor(.5, .5, .5, 1);
			glewInit();

			glEnable(GL_TEXTURE_2D);

			while (w->ON && !glfwWindowShouldClose(w->w)) {
				if (!w->PAUSE) {
					glfwPollEvents();

					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					for (auto& o : *w->obj)
						o->stage(STG_RENDER);

					int W, H;
					glfwGetWindowSize(w->w, &W, &H);
					glViewport(0, 0, W, H);

					glfwSwapBuffers(w->w);
				};
			};
		};

		GLFWwindow* w = NULL;
	};

	namespace game {
		Window* create() {
			Window* w = new Window();

			return w;
		};
	}

	namespace res {
		Window* create() {
			return new Window();
		};
	}

	void init(Window* w) {

	};
	void reset(Window* w) {

	};
};
