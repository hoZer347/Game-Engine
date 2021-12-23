#pragma once

#include "Mesh.h"

#include <functional>
#include <string>
#include <map>

// Does an animation based on a function f and memory mem
class Animation : public MeshObj{
public:
	Animation();
	void update();

	// Memory for the animation to use
	std::vector<void*> mem;

	// A function that updates obj every frame
	std::function<void(Animation*)> f = [](void*) {};
};

extern std::map<std::string, Animation*> ANMT;

// Creates an animation
static Animation* create_animation(std::string s) {
	Animation* a = new Animation();

	ANMT[s] = a;
	OBJS.push_back(a);

	return a;
};

// Stops all animations from animating
static void stop_animations() {
	for (auto& i : ANMT)
		i.second->animate = false;
};
