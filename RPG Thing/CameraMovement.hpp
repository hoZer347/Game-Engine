#pragma once

#include "Inputs.h"
#include "Renderer.h"

static void wasd_strafes_camera(Renderer* r) {
	inputs.mem["Renderer"] = r;

	inputs.f[GLFW_KEY_W] = []() {
		Renderer* r = (Renderer*)inputs.mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(0, 0, .1, 0)));
	};

	inputs.f[GLFW_KEY_A] = []() {
		Renderer* r = (Renderer*)inputs.mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(.1, 0, 0, 0)));
	};

	inputs.f[GLFW_KEY_S] = []() {
		Renderer* r = (Renderer*)inputs.mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(0, 0, -.1, 0)));
	};

	inputs.f[GLFW_KEY_D] = []() {
		Renderer* r = (Renderer*)inputs.mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(-.1, 0, 0, 0)));
	};
}

static void rm_drag_rotates_camera(Renderer* r) {
	inputs.mem["Renderer"] = r;
	
	inputs.f[GLFW_MOUSE_BUTTON_RIGHT] = []() {
		Renderer* r = (Renderer*)inputs.mem["Renderer"];

		r->c->yaww = rotate(r->c->yaww, radians((float)inputs.dx), vec3(0, 1, 0));
	};
}

static void scroll_zooms_camera(Renderer* r) {
	inputs.mem["Renderer"] = r;
	glfwSetWindowUserPointer(inputs.window, &inputs);

	glfwSetScrollCallback(
		inputs.window,
		[](GLFWwindow*, double x, double y) {
			Renderer* r = (Renderer*)((Inputs*)glfwGetWindowUserPointer(inputs.window))->mem["Renderer"];

			r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(0, y, y, 0)));
		});
}

static void all_camera_movement(Renderer* r) {
	wasd_strafes_camera(r);
	rm_drag_rotates_camera(r);
	scroll_zooms_camera(r);
}
