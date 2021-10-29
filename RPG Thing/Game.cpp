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

        vec4 v = vec4(0);

        vec3 ray_cds = vec3(-1.0f + (2.0f * i->mx) / w, 1.0f - (2.0f * i->my) / h, 1);
        vec4 ray_clp = vec4(ray_cds.x, ray_cds.y, -1, 1);

        vec4 ray_eye = inverse(c->proj) * ray_clp;
        ray_eye = vec4(ray_eye.x, ray_eye.y, -1, 0);
        vec3 ray_wld = vec3(inverse(c->view) * ray_eye);
        ray_wld = normalize(ray_wld);

        v = inverse(c->mode) * vec4(ray_wld, 1);

        std::cout <<
            v.x << "," <<
            v.y << "," <<
            v.z << "," <<
            std::endl;

        Mesh* m = MESH[1];

        m->vtxs[0].pos = vec3(v) + vec3(inverse(c->rotn) * vec4(0, 0, .99, 1));
        m->vtxs[1].pos = vec3(v) + vec3(inverse(c->rotn) * vec4(1, 0, .99, 1));
        m->vtxs[2].pos = vec3(v) + vec3(inverse(c->rotn) * vec4(1, 1, .99, 1));
        m->vtxs[3].pos = vec3(v) + vec3(inverse(c->rotn) * vec4(0, 1, .99, 1));

        i->update();
        g->update();
        r->update();

        update_timer();

        for (auto& s : SPRS)
            s->update();
    }
}
