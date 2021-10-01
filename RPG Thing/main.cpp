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

    r.add(Vtx({ vec3(1, 1, 0) }));
    r.add(Vtx({ vec3(0, 1, 0) }));
    r.add(Vtx({ vec3(0, 0, 0), vec4(1, 0, 0, 0) }));
    r.add(Vtx({ vec3(0, 0, 0), vec4(1, 0, 0, 0) }));
    r.add(Vtx({ vec3(0, 0, 1) }));
    r.add(Vtx({ vec3(0, 1, 1) }));

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
