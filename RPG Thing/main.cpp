#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Game.h"
#include "Grid.h"
#include "Text.h"
#include "Sprite.h"

// Tasks
// TODO: Add shadows
// TODO: Add sound
// TODO: Find out the normal of a 3D function
// TODO: Add menus
// TODO: Add dialogue script

// Bugs

using namespace glm;

int main() {
    FT_Init_FreeType(&lib);
    Game game;

    auto g = create_grid(100, 100, a_sinx_sinz);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
