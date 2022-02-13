#include "RendererActions.h"

#include "Renderer.h"
#include "Camera.h"
#include "Window.h"
#include "Inputs.h"
#include "Mesh.h"

enum CM {
	MIN_W = 640,
	MIN_H = 640,
	MAX_W = GLFW_DONT_CARE,
	MAX_H = GLFW_DONT_CARE
};

void wasd_strafes_camera() {
	inputs->f.push_back([]() {
		if (glfwGetKey(WINDOW, GLFW_KEY_W)) {
			Renderer* r = RENDERER;

			r->c->trns = translate(r->c->trns,
				vec3(inverse(r->c->yaww) * vec4(0, 0, .1, 0)));
		}
		});

	inputs->f.push_back([]() {
		if (glfwGetKey(WINDOW, GLFW_KEY_A)) {
			Renderer* r = RENDERER;

			r->c->trns = translate(r->c->trns,
				vec3(inverse(r->c->yaww) * vec4(.1, 0, 0, 0)));
		}
		});

	inputs->f.push_back([]() {
		if (glfwGetKey(WINDOW, GLFW_KEY_S)) {
			Renderer* r = RENDERER;

			r->c->trns = translate(r->c->trns,
				vec3(inverse(r->c->yaww) * vec4(0, 0, -.1, 0)));
		}
		});

	inputs->f.push_back([]() {
		if (glfwGetKey(WINDOW, GLFW_KEY_D)) {
			Renderer* r = RENDERER;

			r->c->trns = translate(r->c->trns,
				vec3(inverse(r->c->yaww) * vec4(-.1, 0, 0, 0)));
		}
		});
}

void mm_drag_rotates_camera() {
	inputs->f.push_back([]() {
		if (glfwGetMouseButton(WINDOW, GLFW_MOUSE_BUTTON_MIDDLE)) {
			Renderer* r = RENDERER;

			r->c->yaww = rotate(r->c->yaww,
				radians((float)inputs->dx), vec3(0, 1, 0));
		}
		});
}

void scroll_zooms_camera() {
	glfwSetWindowUserPointer(WINDOW, &inputs);

	inputs->s = [](double x, double y) {
		Renderer* r = RENDERER;

		r->c->trns = translate(r->c->trns, vec3(inverse(r->c->yaww) * vec4(0, y, y, 0)));
	};
}

void set_min_window_size() {
	glfwSetWindowSizeLimits(
		WINDOW,
		CM::MIN_W, CM::MIN_H,
		CM::MAX_W, CM::MAX_H);
}

void isometric_mount_camera() {
	Renderer* r = RENDERER;

	r->c->trns = translate(mat4(1), vec3(0, -10, -10));
	r->c->roll = rotate(mat4(1), radians(45.f), vec3(1, 0, 0));
}

void setup_camera_movement() {
	wasd_strafes_camera();
	mm_drag_rotates_camera();
	scroll_zooms_camera();
	set_min_window_size();
}
