#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Game.h"

// Tasks
// TODO: Add shadows
// TODO: Add sound
// TODO: Find out the normal of a 3D function
// TODO: Add menus
// TODO: Add dialogue script

// Bugs

using namespace glm;

int main() {
    Game game;

    int i = 0;

    auto sprite = create_sprite();
    bind_texture(sprite);
    sprite->mesh->trns = translate(sprite->mesh->trns, vec3(-1, -1, 0));
    sprite->mesh->ortho = true;

    auto m1 = create_plane(10, 10);
    change_rendering(m1, GL_LINES);

    auto f = create_font();
    auto t1 = create_text("Testing", f);

    clear_font(f);

    auto t2 = create_text("OMG", f);
    translate_text(t1, vec3(0, 0, 1));

    for (auto& i : m1->vtxs)
        y_is_negz(i);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
