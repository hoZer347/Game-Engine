#pragma once

#include "Inputs.h"
#include "Renderer.h"

#include "Grid.h"

static void wasd_strafe_camera(Renderer* r) {
	Input* i;

	i = new Input();

	i->mem.push_back(r);
	i->f = [](Input* i) {
		Renderer* r = (Renderer*)i->mem[0];

		r->c->trns = translate(r->c->trns, vec3(0, 0, .1));
	};
	inputs[GLFW_KEY_W] = i;

	i = new Input();

	i->mem.push_back(r);
	i->f = [](Input* i) {
		Renderer* r = (Renderer*)i->mem[0];

		r->c->trns = translate(r->c->trns, vec3(.1, 0, 0));
	};
	inputs[GLFW_KEY_A] = i;

	i = new Input();

	i->mem.push_back(r);
	i->f = [](Input* i) {
		Renderer* r = (Renderer*)i->mem[0];

		r->c->trns = translate(r->c->trns, vec3(0, 0, -.1));
	};
	inputs[GLFW_KEY_S] = i;

	i = new Input();

	i->mem.push_back(r);
	i->f = [](Input* i) {
		Renderer* r = (Renderer*)i->mem[0];

		r->c->trns = translate(r->c->trns, vec3(-.1, 0, 0));
	};
	inputs[GLFW_KEY_D] = i;
}
