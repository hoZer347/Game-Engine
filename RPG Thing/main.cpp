#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "CameraMovement.hpp"
#include "GridInteraction.hpp"
#include "Timer.h"
#include "Dialogue.hpp"
#include "Grid.h"
#include "Sprite.h"

// TODO: Unit
// TODO: Menus
// TODO: Sound
// TODO: Shadows
// TODO: Dialogues
// TODO: Serialization
// TODO: Grid Interaction

using namespace glm;

int main() {

    // Experimentation code
    auto clock = start_clock();
    auto renderer = create_renderer();
    auto grid = create_grid(renderer);
    auto sprite = create_sprite(renderer);
    auto unit = create_unit();
    all_camera_movement(renderer);
    setup_grid(grid);
    attach_neighbours(grid);

    auto d = create_dialogue(renderer);

    grid->C[3][3]->u = unit;
    unit->s = sprite;
    bind_texture(sprite);

    Camera* c = renderer->c;
    c->trns = translate(c->trns, vec3(0, -10, -10));
    c->roll = rotate(c->roll, radians(45.f), vec3(1, 0, 0));
    //

    // Execution code
    renderer->init();

    delete unit;
    do_timer = false;
    clock.join();

    unload_faces();
    clear_mesh();
    glfwTerminate();
    if (inputs) delete inputs;
    //

    return 0;
}
