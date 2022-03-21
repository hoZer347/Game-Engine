// Memory Tracking
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
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
    inputs::next();
    cam::create();

    mesh::Mesh m;
    m.vtxs = { 0, 0, 0 };
    m.inds = { 0 };
    m.add_attrib(3);
    m.drawing_mode = GL_POINTS;
    m.set_shader(
        "Position_Basic.vert",
        "Quads_Basic.geom",
        "Texture_Basic.frag"
    );
    m.add_texture("DK.png");
    m.setup();

    renderer::init();

    return 0;
};
