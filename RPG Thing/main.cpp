// Memory Tracking
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Native Imports
#include "Object.h"
using namespace obj;

#include "Mesh.h"
using namespace mesh;

#include "Sprite.h"

#include "Inputs.h"
#include "Renderer.h"

// Standard imports
#include <iostream>

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    std::vector<float> vtxs = {
        0, 0, 0,
    };

    std::vector<unsigned int> inds = {
        0,
    };

    sprite::Sprite* s = sprite::create("Textures/Anna.png", vec2(32), vec4(0));
    sprite::pump(s, vtxs);
    sprite::pump(s, inds);

    inputs::next();

    renderer::init();

    return 0;
}
