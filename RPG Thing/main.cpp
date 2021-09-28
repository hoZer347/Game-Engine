#include <GL/glew.h>
#include <GL/glfw3.h>
#include <stdio.h>

#include "Renderer.h"

using namespace glm;

int main() {
    Renderer r;

    r.add(Vtx({ vec3(1, 1, 0) }));
    r.add(Vtx({ vec3(0, 1, 0) }));
    r.add(Vtx({ vec3(0, 0, 0), vec4(1, 0, 0, 0) }));
    r.add(Vtx({ vec3(0, 0, 0), vec4(1, 0, 0, 0) }));
    r.add(Vtx({ vec3(0, 0, 1) }));
    r.add(Vtx({ vec3(0, 1, 1) }));

    while (!glfwWindowShouldClose(r.window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(r.shader_programme);
        glBindVertexArray(r.vao);

        r.update();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwPollEvents();

        glfwSwapBuffers(r.window);
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}
