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

void test() {
    std::cout << "hi" << std::endl;
};

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    spooler::push(test, 0);



    spooler::close();

    return 0;
};
