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
#include "Mesh.h"
#include "Sprite.h"
#include "Shaders.h"
#include "Inputs.h"
#include "Renderer.h"
#include "Particle.h"
#include "Depth.h"
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
    auto l1 = cam::light::create();
    //auto d1 = depth::create();
    auto d2 = depth::create(l1);

    cam::create();

    sprite::Sprite* s1 = sprite::create(
        "Textures/Anna.png",
        vec2(32), vec2(0));
    sprite::Sprite* s2 = sprite::create(
        "Textures/Anna.png",
        vec2(32), vec2(0));
    sprite::Sprite* s3 = sprite::create(
        "Textures/Anna.png",
        vec2(32), vec2(0));

    mesh::trns(s1) = translate(mesh::trns(s1), vec3(2, 0, -1));
    mesh::trns(s2) = translate(mesh::trns(s2), vec3(2, 0, -2));
    mesh::trns(s3) = translate(mesh::trns(s3), vec3(2, 0, -3));

    auto f1 = geo::square::create();
    auto f2 = geo::square::create();

    geo::add_texture(f1, "Textures/Stone.png");
    geo::add_texture(f2, "Textures/Stone.png");

    mesh::trns(f1) *= translate(vec3(-5, -5, 5));
    mesh::trns(f1) *= rotate(radians(-90.f), vec3(1, 0, 0));
    mesh::trns(f2) *= rotate(radians(-90.f), vec3(1, 0, 0));
    mesh::trns(f1) *= scale(vec3(10, 10, 0));

    renderer::init();

    //depth::del(d1);
    depth::del(d2);

    return 0;
};
