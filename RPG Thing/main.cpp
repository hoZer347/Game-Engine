#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "Inputs.h"
#include "Timer.h"
#include "Grid.h"
#include "Text.h"
#include "Sprite.h"
#include "Unit.h"

// Tasks
// TODO: Add shadows
// TODO: Add sound
// TODO: Find out the normal of a 3D function
// TODO: Add menus

// Doing
// TODO: Add dialogues

// Bugs

using namespace glm;

int main() {
    FT_Init_FreeType(&lib);

    auto clock = start_clock();
    auto renderer = create_renderer();
    auto grid = create_grid(renderer);
    auto spr = create_sprite();

    spr->m->trns = translate(mat4(1), vec3(-.5, -.5, -10));
    bind_texture(spr);

    renderer->init();

    do_timer = false;
    clock.join();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
