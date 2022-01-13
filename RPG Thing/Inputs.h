#pragma once

#include <glm/glm.hpp>

#include "Window.h"
#include "Camera.h"

#include <functional>
#include <vector>
#include <map>

#include <iostream>

using namespace glm;

enum {
	CAM_EYE=0,
	CAM_RAY=1
};

class Inputs {
public:
	~Inputs();
	void update();

	double
		mx=0, my=0, // Current mouse pos
		dx=0, dy=0; // Delta mouse pos
	
	// Memory for inputs to use
	std::map<const char*, void*> mem;
	
	// Every-tick inputs for mouse and keyboard
	std::vector<std::function<void()>> f;

	// Window keyboard inputs
	std::map<short, std::function<void(int, int, int)>> k;
	
	// Window mouse inputs
	std::map<short, std::function<void(int, int)>> m;
	
	// Cursor movement
	std::function<void(double, double)> c = [](double, double) {};
	
	// Scroll input
	std::function<void(double, double)> s = [](double, double) {};

	// Functions to run on deletion
	std::vector<std::function<void()>> on_del;

	// Updated through renderer
	mat2x3 mouse_ray = mat2x3(0);

	// The previous inputs in the chain
	Inputs* _prev = NULL;
};

extern Inputs* inputs;

//
extern void init_inputs();

//
extern void new_inputs();

//
extern void prev_inputs();
