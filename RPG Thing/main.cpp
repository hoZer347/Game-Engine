#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>

#include "SOIL/SOIL.h"

#include "Game.h"

using namespace glm;

#include <functional>

int main() {
    Room* room = create_room(new Grid(32, 32));

    Renderer* r = room->r;
    Inputs* _i = room->i;
    Container* con = room->c;
    Camera* c = r->c;

    glEnable(GL_TEXTURE_2D);

    // Anti-aliasing
    glEnable(GL_MULTISAMPLE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    //

    // Blocking stuff that are behind opaque objects
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    //

    // Alpha processing setup
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);
    //

    // Culling faces that don't face the camera
    glEnable(GL_CULL_FACE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    Renderable faces, lines;

    //r->add("Faces", GL_QUADS);
    //r->bind(faces);

    r->add("Lines", GL_LINES);
    r->bind(lines);

    create_planes(&faces, &lines, 8, 4);

    r->add("Textures/Cpt.png", GL_QUADS);

    r->add(r->size());
    r->add(Vtx({ vec3(0, 1, 0), vec4(1), vec3(0, 1, 0), vec2(0, 0) }));
    r->add(r->size());
    r->add(Vtx({ vec3(0, 1, -1), vec4(1), vec3(0, 1, 0), vec2(1, 0) }));
    r->add(r->size());
    r->add(Vtx({ vec3(-1, 1, -1), vec4(1), vec3(0, 1, 0), vec2(1, 1) }));
    r->add(r->size());
    r->add(Vtx({ vec3(-1, 1, 0), vec4(1), vec3(0, 1, 0), vec2(0, 1) }));

    Game game = Game(room);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}
