#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>

#include "SOIL/SOIL.h"

#include "Renderer.h"
#include "Inputs.h"

using namespace glm;

int main() {
    Renderer r;
    Inputs _i(r.window);
    Camera* c = r.get_cam();

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

    r.add(Vtx({ vec3(-100, 0, -100) }));
    r.add(Vtx({ vec3(-100, 0,  100) }));
    r.add(Vtx({ vec3( 100, 0,  100) }));
    r.add(Vtx({ vec3( 100, 0, -100) }));

    r.add(0);
    r.add(1);
    r.add(2);
    r.add(2);
    r.add(3);
    r.add(0);

    r.texs.push_back(Vtx({ vec3(-1, 1, -1), vec4(), vec3(), vec2(0, 0) }));
    r.texs.push_back(Vtx({ vec3(-1, 1,  1), vec4(), vec3(), vec2(0, 1) }));
    r.texs.push_back(Vtx({ vec3( 1, 1,  1), vec4(), vec3(), vec2(1, 1) }));
    r.texs.push_back(Vtx({ vec3( 1, 1, -1), vec4(), vec3(), vec2(1, 0) }));

    r.tnds.push_back(0);
    r.tnds.push_back(1);
    r.tnds.push_back(2);
    r.tnds.push_back(3);

    r.add("Cpt.png");

    for (auto& i : r.vtxs)
        i.pos -= vec3(0.5f, 0.5f, 0.5f);
    for (auto& i : r.texs)
        i.pos -= vec3(0.5f, 0.5f, 0.5f);

    c->view = lookAt(vec3(0, 5, -5), vec3(0, 0, 0), c->up);
    c->mode = translate(mat4(1.0f), vec3(0, -5, 5));
    c->proj = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(r.window)) {

        c->mode = rotate(c->mode, radians(1.0f), c->up);

        _i.update();
        r.update();
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}
