#include "Game.h"
#include "glm/gtx/intersect.hpp"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

void Game::init() {
    Camera* c = room->r->c;
    Container* g = room->c;
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

        // https://antongerdelan.net/opengl/raycasting.html

        vec4 v = vec4(0);

        vec3 ray_cds = vec3(-1.0f + (2.0f * i->mx)/w, 1.0f - (2.0f * i->my)/h, 1);
        vec4 ray_clp = vec4(ray_cds.x, ray_cds.y, -1, 1);

        vec4 ray_eye = inverse(c->proj) * ray_clp;
        ray_eye = vec4(ray_eye.x, ray_eye.y, -1, 0);
        vec3 ray_wld = vec3(inverse(c->view) * ray_eye);
        ray_wld = normalize(ray_wld);
        
        v = vec4(ray_wld, 1);

        //std::cout <<
        //    v.x << "," <<
        //    v.y << "," <<
        //    v.z << "," <<
        //    std::endl;

        //Mesh* m = MESH[0];

        //*m = vec3(v);

        i->update();
        g->update();
        r->update();

        millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;
    }
}
