#pragma once

#include <GLFW/glfw3.h>

#include <map>
#include <vector>
#include <string>

class Inputs {
public:
	Inputs(GLFWwindow*);
	void update();

	void clear() { listeners.clear(); output.clear(); };
	auto begin() { return output.begin(); };
	auto end() { return output.end(); };
	auto& operator[](int i) { return listeners[i]; };

private:
	std::vector<int> output;
	std::map<int, int> listeners;
	GLFWwindow* window = NULL;
};

