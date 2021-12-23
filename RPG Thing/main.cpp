#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "Inputs.hpp"
#include "Timer.h"
#include "Grid.h"
#include "Sprite.h"

// Tasks
// TODO: Add shadows
// TODO: Find out the normal of a 3D function
// TODO: Add menus
// TODO: Change timer to glfw timer

// Doing
// TODO: Add dialogues
// TODO: Add sound

// Bugs

using namespace glm;

int main() {

    // Experimentation code
    auto clock = start_clock();
    auto renderer = create_renderer();
    auto grid = create_grid(renderer);
    auto spr = create_sprite();
    wasd_strafe_camera(renderer);

    spr->m->trns = translate(mat4(1), vec3(-.5, -.5, -10));
    bind_texture(spr);

    Camera* c = renderer->c;
    c->trns = translate(c->trns, vec3(0, -10, -10));
    c->rotn = rotate(c->rotn, radians(45.f), vec3(1, 0, 0));
    //

    // Execution code
    renderer->init();

    do_timer = false;
    clock.join();

    glfwTerminate();
    //

    return 0;
}
