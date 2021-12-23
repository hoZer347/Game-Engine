#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "Inputs.h"
#include "Timer.h"
#include "Grid.h"
#include "Text.h"
#include "Sprite.h"
#include "Sound.h"

// Tasks
// TODO: Add shadows
// TODO: Find out the normal of a 3D function
// TODO: Add menus

// Doing
// TODO: Add dialogues
// TODO: Add sound

// Bugs

using namespace glm;

int main() {
    FT_Init_FreeType(&lib);

    // auto music = SOUND->play2D("Sounds/The First Night.wav", true);

    auto clock = start_clock();
    auto renderer = create_renderer();
    auto grid = create_grid(renderer);
    auto spr = create_sprite();

    spr->m->trns = translate(mat4(1), vec3(-.5, -.5, -10));
    bind_texture(spr);

    Camera* c = renderer->c;
    c->trns = translate(c->trns, vec3(0, -10, -10));
    c->roll = rotate(c->roll, radians(45.f), vec3(1, 0, 0));

    renderer->init();

    do_timer = false;
    clock.join();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
