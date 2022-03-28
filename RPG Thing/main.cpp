// Memory Tracking
#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
#include <crtdbg.h>

// GL imports
#include <GLFW/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

// Native Imports
#include "Object.h"
#include "Camera.h"
#include "Sprite.h"
#include "Perspective.h"
#include "Mesh.h"
#include "Inputs.h"
#include "Renderer.h"
#include "Geo.h"
#include "GridFactory.h"

// Standard imports
#include <iostream>
#include <thread>

/* TODOS:
Working on:
- Add shadows
    - Finished depth map
    - Need to adapt current shaders to work with depth map

Planned:
- Add "shatter" effect onto sprites in particle
- Add Grid
- Add deletion-optimized std::vector wrapper
- Add thread task system

Small / Debug:
- Changing lighting.x files to depth.x
- Add custom deletion to textures.h and shaders.h
- Fix crashing after closing

Might Implement:
- Synchronize with time, not frames (Not Required)

*/

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    renderer::setup();

    auto s = sprite::create("Anna.png");
    cam::trns *= translate(vec3(0, -1, -1));
    cam::roll *= rotate(45.f, vec3(1, 0, 0));
    mesh::trns(s) *= translate(vec3(0, 0, 0));

    renderer::init();

    grid::load();

    renderer::close();

    grid::close();

    return 0;
};
