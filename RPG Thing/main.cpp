#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Game.h"
#include "Logic.hpp"
#include "Grid.h"
#include "Text.h"
#include "Sprite.h"
#include "Unit.h"

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

    auto g = create_grid(10, 10, a_sinx_sinz, true);
    g->c[5][5]->u = create_unit();
    g->get = get_cam_ray;
    g->r = game.room;

    free_camera(game.room);
    scroll_zooms_camera(game.room);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
