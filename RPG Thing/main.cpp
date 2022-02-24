// Memory Tracking
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Native Imports
#include "Object.h"
#include "Mesh.h"
#include "Renderer.h"

// Standard imports
#include <iostream>

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    mesh::Lines* lines = new mesh::Lines();

    std::vector<float> v1({ 0, 0, 0, 1, 1, 0, 1, 0, 0 });
    std::vector<unsigned int> v2({ 0, 1, 1, 2, 2, 0 });

    lines->pump(v1, 0);
    lines->pump(v2, 0);

    renderer::init();

    return 0;
}
