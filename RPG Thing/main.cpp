#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Game.h"

using namespace glm;

int main() {
    Room* room = create_room();

    auto m1 = create_plane(10, 10);
    auto m2 = create_square();

    bind_texture("Textures/DK.png", m2);
    *m2 -= vec3(1, 0, 0);

    *m1 *= rotate(mat4(1), radians(90.f), vec3(1, 0, 0));

    //change_rendering(m1, GL_LINES);

    Game game = Game(room);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}
