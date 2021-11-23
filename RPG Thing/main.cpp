#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Game.h"

// Tasks
// TODO: Add shadows
// TODO: Add sound
// TODO: Find out the normal of a 3D function

// Bugs
// TODO: Sprites are blurry

using namespace glm;

int main() {
    Game game;

    auto sprite = create_sprite();
    bind_texture(sprite);

    auto f = create_font();

    auto m1 = create_plane(10, 10);
    auto t = create_text("\nTesting", f);

    change_rendering(m1, GL_LINES);

    for (auto& i : m1->vtxs)
        y_is_negz(i);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
