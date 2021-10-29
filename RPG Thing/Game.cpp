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

        // Testing mouse-to-object stuff
        int w = 0, h = 0;
        glfwGetWindowSize(room->r->window, &w, &h);

        // https://antongerdelan.net/opengl/raycasting.html

        vec4 v = vec4(1);

        vec4 eye = vec4((i->mx - w/2) / (w/2), (-i->my + h/2) / (h/2), 0, 1);
             eye = inverse(c->mvp) * eye;
             eye /= eye.w;
        
        vec4 ray = vec4(c->look - c->eye, 1);
             ray = inverse(c->mode) * ray;
             ray /= ray.w;

        v = eye;
   
        std::cout <<
            v.x << "," <<
            v.y << "," <<
            v.z << "," <<
            v.w << "," <<
            std::endl;

        Mesh* m = MESH[1];

        m->vtxs[0].pos = vec3(v) + vec3(vec4(0, 0, 0, 0));
        m->vtxs[1].pos = vec3(v) + vec3(vec4(1, 0, 0, 0));
        m->vtxs[2].pos = vec3(v) + vec3(vec4(1, 1, 0, 0));
        m->vtxs[3].pos = vec3(v) + vec3(vec4(0, 1, 0, 0));

        v = ray;

        m = MESH[2];

        m->vtxs[0].pos = vec3(v) + vec3(vec4(0, 0, 0, 0));
        m->vtxs[1].pos = vec3(v) + vec3(vec4(1, 0, 0, 0));
        m->vtxs[2].pos = vec3(v) + vec3(vec4(1, 1, 0, 0));
        m->vtxs[3].pos = vec3(v) + vec3(vec4(0, 1, 0, 0));

        for (auto& s : SPRS)
            s->update();

        i->update();
        g->update();
        r->update();

        update_timer();
    }
}
