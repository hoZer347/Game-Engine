#pragma once

#include "Mesh.h"

#include <functional>
#include <string>
#include <map>

// Does an animation based on a function f and memory mem
class Animation : public MeshObj<Animation> {
public:
	Animation();
	void update();

	// Memory for the animation to use
	std::map<std::string, void*> mem;

	// A function that updates obj every frame
	std::function<void(Animation*)> f = [](Animation*) {};
};

extern std::map<std::string, Animation*> ANMT;

// Creates an animation
extern Animation* create_animation(std::string s);

// Stops all animations from animating
extern void stop_animations();
