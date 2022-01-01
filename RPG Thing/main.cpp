#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "CameraMovement.hpp"
#include "GridInteraction.hpp"
#include "Timer.h"
#include "Dialogue.hpp"
#include "Unit.hpp"
#include "Grid.h"
#include "Sprite.h"
#include "Text.h"

// TODO: Unit
// TODO: Menus
// TODO: Sound
// TODO: Shadows
// TODO: Dialogues
// TODO: Serialization
// TODO: Grid Interaction

using namespace glm;

int main() {
    FT_Init_FreeType(&lib);

    // Experimentation code
    auto clock = start_clock();
    auto renderer = create_renderer();
    auto grid = create_grid(renderer);
    auto sprite = create_sprite(renderer);
    auto unit = create_unit();
    auto text = create_text();
    all_camera_movement(renderer);
    setup_grid(grid);
    attach_neighbours(grid);

    auto unit_menu = UnitOptions::get_options(unit);

    grid->set(unit, 3, 3);
    unit->s = sprite;
    bind_texture(sprite);

    Camera* c = renderer->c;
    c->trns = translate(c->trns, vec3(0, -10, -10));
    c->roll = rotate(c->roll, radians(45.f), vec3(1, 0, 0));
    //

    // Execution
    renderer->init();

    // Deallocation
    delete unit;
    do_timer = false;
    clock.join();

    clear_mesh();
    glfwTerminate();
    if (inputs) delete inputs;

    FT_Done_FreeType(lib);
    //

    return 0;
}
