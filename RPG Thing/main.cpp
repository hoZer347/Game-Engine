// Memory Tracking
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// GL imports
#include <GLFW/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include <cuda_runtime.h>

// STD Imports
#include <iostream>

// Local Imports
#include "Spooler.h"
#include "Object.h"
#include "Window.h"

#include <stack>
#include <thread>

__global__ void kernel() {

};

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    bool b = false;

    std::vector<std::thread> v;

    std::stack<size_t> s;
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    s.push(s.size());
    std::stack<size_t> _s;

    v.push_back(std::thread([&b, &s]() {
        while (!b) {}

        while (s.size()) {
            std::cout << s.top();
            s.pop();
        };

        }));

    b = true;

    return 0;
};
