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

// STD Imports
#include <iostream>

// Local Imports
#include "Spooler.h"

void test0() {
    int i = 0;
};

void test1() {
    int i = 0;
};

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    spooler::push(test0);
    spooler::push(test1);
    spooler::push(test0);

    spooler::close();

    for (auto i = 0; i < 10000000; i++)
        std::cout << "hi" << std::endl;

    return 0;
};
