#include "Inputs.h"

#include "Spooler.h"

#include <time.h>
#include <atomic>
#include <vector>

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace inputs {
	std::thread _t;
	
	bool KILL = false;

	void update() {
		glfwPollEvents();
	};

	void kernel(double t) {
		std::clock_t c;

		while (!KILL) {
			c = clock() + (int)t;
			while (clock() < c);
			update();
		};
	};
	
	void init(double t) {
		_t = std::thread(kernel, t);
	};

	void close() {
		KILL = true;
		_t.join();
	};
};
