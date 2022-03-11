#include "Camera.h"

#include "Window.h"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
using namespace glm;

namespace cam {
	mat4
		trns = mat4(1),
		rotn = mat4(1),
		mode = mat4(1),
		view = mat4(1),
		proj = mat4(1),
		mvp  = mat4(1);

	void update() {
		int w, h;
		glfwGetWindowSize(WINDOW, &w, &h);

		rotn = rotn * rotate(radians(1.f), vec3(0, 1, 0));

		mode = rotn * trns;
		view = lookAt(
			vec3(0, 0, 2),
			vec3(0, 0, 0),
			vec3(0, 1, 0));
		proj = perspective(radians(45.f), (float)w / (float)h, .1f, 1000.f);
		mvp = proj * view * mode;
	};
};
