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
#include "Particle.h"
#include "Lighting.h"
#include "Geo.h"

// Standard imports
#include <iostream>

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

/* TODOS:
Working on:
- Add shadows
    - Finished depth map
    - Need to adapt current shaders to work with depth map

Planned:
- Add "shatter" effect onto sprites in particle
- Add Grid

Small / Debug:
- Changing lighting.x files to depth.x
- Add custom deletion to textures.h and shaders.h

Might Implement:
- Synchronize with time, not frames (Not Required)

*/

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    std::vector<float> vtxs = {
        0, 0, 0,
    };

    std::vector<unsigned int> inds = {
        0,
    };

    renderer::setup();

    sprite::Sprite* s1 = sprite::create(
        "Textures/Anna.png",
        vec2(32), vec2(0));
    sprite::Sprite* s2 = sprite::create(
        "Textures/Anna.png",
        vec2(32), vec2(0));
    sprite::Sprite* s3 = sprite::create(
        "Textures/Anna.png",
        vec2(32), vec2(0));
    sprite::pump(s1, vtxs);
    sprite::pump(s1, inds);
    sprite::pump(s2, vtxs);
    sprite::pump(s2, inds);
    sprite::pump(s3, vtxs);
    sprite::pump(s3, inds);
    mesh::trns(s1) = translate(mesh::trns(s1), vec3(2, 0, -1));
    mesh::trns(s2) = translate(mesh::trns(s2), vec3(2, 0, -2));
    mesh::trns(s3) = translate(mesh::trns(s3), vec3(2, 0, -3));

    auto f1 = geo::square::create();
    auto f2 = geo::square::create();

    mesh::trns(f1) *= translate(vec3(-5, -5, 5));
    mesh::trns(f1) *= rotate(-90.f, vec3(1, 0, 0));
    mesh::trns(f2) *= rotate(-90.f, vec3(1, 0, 0));
    mesh::trns(f1) *= scale(vec3(10, 10, 0));

    renderer::init();

    geo::square::del(f1);
    geo::square::del(f2);

    sprite::del(s1);
    sprite::del(s2);
    sprite::del(s3);

    return 0;
};
