#pragma once

#include "inputs.h"
#include "Renderer.h"

enum CM {
	MIN_W = 640,
	MIN_H = 640,
	MAX_W = GLFW_DONT_CARE,
	MAX_H = GLFW_DONT_CARE
};

static void wasd_strafes_camera(Renderer* r) {
	inputs->mem["Renderer"] = r;

	inputs->f[GLFW_KEY_W] = []() {
		Renderer* r = (Renderer*)inputs->mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(0, 0, .1, 0)));
	};

	inputs->f[GLFW_KEY_A] = []() {
		Renderer* r = (Renderer*)inputs->mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(.1, 0, 0, 0)));
	};

	inputs->f[GLFW_KEY_S] = []() {
		Renderer* r = (Renderer*)inputs->mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(0, 0, -.1, 0)));
	};

	inputs->f[GLFW_KEY_D] = []() {
		Renderer* r = (Renderer*)inputs->mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(-.1, 0, 0, 0)));
	};
}

static void mm_drag_rotates_camera(Renderer* r) {
	inputs->mem["Renderer"] = r;
	
	inputs->f[GLFW_MOUSE_BUTTON_MIDDLE] = []() {
		Renderer* r = (Renderer*)inputs->mem["Renderer"];

		r->c->yaww = rotate(r->c->yaww, radians((float)inputs->dx), vec3(0, 1, 0));
	};
}

static void scroll_zooms_camera(Renderer* r) {
	inputs->mem["Renderer"] = r;
	glfwSetWindowUserPointer(inputs->window, &inputs);

	inputs->s = [](double x, double y) {
		Renderer* r = (Renderer*)inputs->mem["Renderer"];

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(0, y, y, 0)));
	};
}

static void set_min_window_size() {
	glfwSetWindowSizeLimits(
		inputs->window,
		CM::MIN_W, CM::MIN_H,
		CM::MAX_W, CM::MAX_H);
}

static void all_camera_movement(Renderer* r) {
	wasd_strafes_camera(r);
	mm_drag_rotates_camera(r);
	scroll_zooms_camera(r);
	set_min_window_size();
}

static void isometric_mount_camera(Renderer* r) {
	r->c->trns = translate(mat4(1), vec3(0, -10, -10));
	r->c->roll = rotate(mat4(1), radians(45.f), vec3(1, 0, 0));
}
