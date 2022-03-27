#include "CameraMovement.h"

#include "Camera.h"
#include "Window.h"
#include "Inputs.h"

namespace inputs {
	void debug_mode() {
		glfwSetCursorPosCallback(
			WINDOW,
			[](GLFWwindow* w, double x, double y) {
				
			});
	};
};
