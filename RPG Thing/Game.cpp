#include "Game.h"

#include <glm/gtx/intersect.hpp>

Game::Game() {
    room = create_room();
}

void Game::init() {
    Camera* c = room->r->c;
    Inputs* i = room->i;
    Renderer* r = room->r;

    glfwSetWindowUserPointer(room->r->window, room);

    free_camera(room);
    scroll_zooms_camera(room);

    while (!glfwWindowShouldClose(room->r->window)) {
        i->update();

        for (auto& m : OBJS)
            if (m->animate)
                m->update();

        r->update();
        
        update_timer();
    }
}
