#include "App.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

namespace app {
	struct App {
		App() {
			glfwInit();
			w = glfwCreateWindow(640, 640, "", NULL, NULL);
			glewInit();
		};
		~App() {
			glfwTerminate();
		};

		void init() {
			while (true);
		};

		GLFWwindow* w = NULL;
	};

	namespace game {
		void create() {
			App a;

			a.init();
		};
	};

	namespace resource {
		void create() {
			
		};
	};
};
