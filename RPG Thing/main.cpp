#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>

#include "Renderer.h"
#include "Inputs.h"

using namespace glm;

int main() {
    Renderer r;
    Inputs _i(r.window);
    Camera* c = r.get_cam();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    r.add(Vtx({ vec3(0, 0, 0), vec4(1, 0, 0, 1) }));    // 0
    r.add(Vtx({ vec3(1, 0, 0) }));                      // 1
    r.add(Vtx({ vec3(0, 0, 1) }));                      // 2
    r.add(Vtx({ vec3(0, 1, 0) }));                      // 3
    r.add(Vtx({ vec3(1, 0, 1) }));                      // 4
    r.add(Vtx({ vec3(0, 1, 1) }));                      // 5
    r.add(Vtx({ vec3(1, 1, 0) }));                      // 6
    r.add(Vtx({ vec3(1, 1, 1), vec4(1, 0, 0, 1) }));    // 7

    r.add(6);
    r.add(1);
    r.add(0);
    r.add(0);
    r.add(3);
    r.add(6);

    r.add(2);
    r.add(4);
    r.add(7);
    r.add(7);
    r.add(5);
    r.add(2);

    r.add("Cpt.png");

    for (auto& i : r.vtxs)
        i.pos -= vec3(0.5f, 0.5f, 0.5f);

    c->view = lookAt(vec3(0, 0, -1), vec3(0, 0, 0), c->up);
    c->mode = translate(mat4(1.0f), vec3(0, 0, 5));
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
