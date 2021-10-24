#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Container.h"

#include <map>
#include <vector>
#include <functional>

struct Room;

typedef void (*Roomfunc) (Room* r);

class Inputs {
public:
	Inputs(GLFWwindow*, Room*);

	void update();

	void clear() { listeners.clear(); };
	void rmv(int i) { listeners.erase(i); };
	auto& operator[](int i) { return listeners[i]; };

	Room* room;
	
	double sx = 0, sy = 0;		// Current mouse pos
	double _sx = 0, _sy = 0;	// Previous mouse pos

	double mx = 0, my = 0;		// Current mouse pos
	double _mx = 0, _my = 0;	// Previous mouse pos

private:
	std::map<int, Roomfunc> listeners;
	GLFWwindow* window = NULL;
};

