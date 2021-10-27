#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Game.h"

#include "Sprite.h"

// Currently doing: Sprite + Timer implementation
// TODO: Add shadows
// TODO: Add sound
// TODO: Sprite Implementation
// TODO: Timer Implementation
// TODO: Get object selection working
// TODO: Find out the normal of a 3D function

using namespace glm;

int main() {
    Room* room = create_room();

    auto m1 = create_plane(10, 10);
    Sprite* s1 = create_sprite();

    bind_texture("Textures/Anna.png", s1);

    m1->trns *= rotate(mat4(1), radians(-90.f), vec3(1, 0, 0));

    Game game = Game(room);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
