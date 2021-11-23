#include "Game.h"

#include <glm/gtx/intersect.hpp>

Game::Game() {
    FT_Init_FreeType(&lib);
    room = create_room();
}

void Game::init() {
    Camera* c = room->r->c;
    Container* g = room->c;
    Inputs* i = room->i;
    Renderer* r = room->r;

    FT_Init_FreeType(&lib);

    glfwSetWindowUserPointer(room->r->window, room);

    free_camera(room);
    scroll_zooms_camera(room);

    while (!glfwWindowShouldClose(room->r->window)) {
        update_sprites();

        i->update();
        g->update();
        r->update();

        update_timer();
    }
}
