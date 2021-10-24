#include "Game.h"
#include "glm/gtx/intersect.hpp"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

void Game::init() {
    Camera* c = room->r->c;
    Inputs* i = room->i;
    Renderer* r = room->r;

    glfwSetWindowUserPointer(room->r->window, room);

    free_camera(room);
    scroll_zooms_camera(room);

    while (!glfwWindowShouldClose(room->r->window)) {
        auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        // Testing mouse-to-object stuff
        int w=0, h=0;
        glfwGetWindowSize(room->r->window, &w, &h);

        vec3 ray = vec3(-1.0f + (2.0f * i->mx)/w, 1.0f - (2.0f * i->my)/h, 1);
        vec4 clp = vec4(ray.x, ray.y, -1, 1);
        vec4 rye = inverse(c->proj) * clp;
        vec4 eye = vec4(rye.x, rye.y, -1, 0);
        vec3 wye = vec3(inverse(c->view) * rye);
        wye = normalize(wye);
        

        i->update();
        room->r->update();

        millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;
        std::cout << millisec_since_epoch << std::endl;
    }
}
