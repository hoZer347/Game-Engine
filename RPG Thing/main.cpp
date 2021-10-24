#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Game.h"

using namespace glm;

int main() {
    Room* room = create_room(new Grid(32, 32));

    auto& m1 = create_square();
    bind_texture("Textures/DK.png", m1);

    auto& m2 = create_square();
    m2.gl_render_type = GL_LINES;

    auto& m3 = create_square();
    m3 *= 10;
    m3 *= rotate(mat4(1), radians(90.0f), vec3(1, 0, 0));
    m3 += vec3(-5, 0, 5);

    Game game = Game(room);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}
