#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "FTL.h"

#include "Sprite.h"

// Currently doing: Object selection
// TODO: Add shadows
// TODO: Add sound
// TODO: Sprite Implementation
// TODO: Timer Implementation
// TODO: Find out the normal of a 3D function

using namespace glm;

int main() {
    Room* room = create_room();

    std::vector<Vtx> vtxs = { Vtx(), Vtx() };
    std::vector<unsigned int> inds = { 0, 1 };

    auto m1 = create_plane(10, 10, 10);
    auto m2 = create_square();
    auto m3 = create_plane(10, 10, 10);

    change_rendering(m1, GL_LINES);
    change_rendering(m3, GL_LINES);

    for (auto& i : m1->vtxs)
        y_is_negz(i);

    FTL game(room);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
