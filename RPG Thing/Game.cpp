#include "Game.h"
#include "glm/gtx/intersect.hpp"

void Game::init() {
    Camera* c = room->r->c;
    Inputs* i = room->i;
    Renderer* r = room->r;
    glfwSetWindowUserPointer(room->r->window, room);

    wasd_strafes_camera(room);
    mouse_rotates_camera(room);
    scroll_zooms_camera(room);

    r->add("Textures/DK.png", GL_QUADS);

    r->add(r->size());
    r->add(Vtx({ vec3(0, 0,  0), vec4(1), vec3(0, 1, 0), vec2(0, 0) }));
    r->add(r->size());
    r->add(Vtx({ vec3(0, 0, -1), vec4(1), vec3(0, 1, 0), vec2(1, 0) }));
    r->add(r->size());
    r->add(Vtx({ vec3(1, 0, -1), vec4(1), vec3(0, 1, 0), vec2(1, 1) }));
    r->add(r->size());
    r->add(Vtx({ vec3(1, 0,  0), vec4(1), vec3(0, 1, 0), vec2(0, 1) }));

    Renderable k;

    r->bind(k);

    while (!glfwWindowShouldClose(room->r->window)) {
        // Testing mouse-to-object stuff
        int w=0, h=0;
        glfwGetWindowSize(room->r->window, &w, &h);
        
        vec4 v = vec4(1, 1, 0, 1);

        v = inverse(c->view) * v;

        r->vtxs[r->curr->inds[0]].pos = vec3(v);
        r->vtxs[r->curr->inds[1]].pos = vec3(v) + vec3(1, 0, 0);
        r->vtxs[r->curr->inds[2]].pos = vec3(v) + vec3(1, 0, -1);
        r->vtxs[r->curr->inds[3]].pos = vec3(v) + vec3(0, 0, -1);

        std::cout << "( "
            << (int)v.x << ","
            << (int)v.y << ","
            << (int)v.z << ","
            << (int)v.w
            << " )" << std::endl;

        i->update();
        room->r->update();
    }
}
