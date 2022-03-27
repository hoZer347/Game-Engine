#include "Inputs.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "Window.h"
#include "Camera.h"
#include "Particle.h"

#include "Object.h"

#include <iostream>

namespace inputs {
	class Inputs : public obj::Obj {
	public:
		Inputs() {
			obj::add(this);
		};
		~Inputs() {
			delete _prev;
		};

		void update() {
			glfwPollEvents();

			if (glfwGetKey(WINDOW, GLFW_KEY_W))
				cam::trns = translate(cam::trns,
					vec3(inverse(cam::yaww) * vec4(  0,   0,  .1, 0)));
			if (glfwGetKey(WINDOW, GLFW_KEY_A))
				cam::trns = translate(cam::trns,
					vec3(inverse(cam::yaww) * vec4( .1,   0,   0, 0)));
			if (glfwGetKey(WINDOW, GLFW_KEY_S))
				cam::trns = translate(cam::trns,
					vec3(inverse(cam::yaww) * vec4(  0,   0, -.1, 0)));
			if (glfwGetKey(WINDOW, GLFW_KEY_D))
				cam::trns = translate(cam::trns,
					vec3(inverse(cam::yaww) * vec4(-.1,   0,   0, 0)));
			if (glfwGetKey(WINDOW, GLFW_KEY_LEFT_CONTROL))
				cam::trns = translate(cam::trns,
					vec3(inverse(cam::yaww) * vec4(  0,  .1,   0, 0)));
			if (glfwGetKey(WINDOW, GLFW_KEY_SPACE))
				cam::trns = translate(cam::trns,
					vec3(inverse(cam::yaww) * vec4(  0, -.1,   0, 0)));

			double
				cx=0, cy=0;
			glfwGetCursorPos(WINDOW, &cx, &cy);

			dx = mx - cx;
			dy = my - cy;

			mx = cx;
			my = cy;

			if (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_RIGHT)) {
				cam::roll = rotate(cam::roll, -(float)dy * .01f, vec3(1, 0, 0));
				cam::yaww = rotate(cam::yaww, -(float)dx * .01f, vec3(0, 1, 0));
			};
		};
		
		double
			dx=0, dy=0,
			mx=0, my=0;

		void render() {

		};

		Inputs
			*_next = NULL,
			*_prev = NULL;
	};

	Inputs* INPUTS = NULL;

	void next() {
		Inputs* i = new Inputs();

		if (INPUTS) {
			INPUTS->_next = i;
			i->_prev = INPUTS;
			INPUTS = INPUTS->_next;
		} else
			INPUTS = i;
	};

	void prev() {
		INPUTS = INPUTS->_prev;
		delete INPUTS->_next;
		INPUTS->_next = NULL;
	};

	void close() {
		delete INPUTS;
	};
};
