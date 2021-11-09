#include "Game.h"

#include <glm/gtx/intersect.hpp>

#include "Sprite.h"

void Game::init() {
    Camera* c = room->r->c;
    Container* g = room->c;
    Inputs* i = room->i;
    Renderer* r = room->r;

    glfwSetWindowUserPointer(room->r->window, room);

    free_camera(room);
    scroll_zooms_camera(room);

    while (!glfwWindowShouldClose(room->r->window)) {
        for (auto& s : SPRS)
            s->update();

        i->update();
        g->update();
        r->update();

        update_timer();
    }
}
