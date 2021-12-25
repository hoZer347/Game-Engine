#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "CameraMovement.hpp"
#include "GridInteraction.hpp"
#include "Timer.h"
#include "Grid.h"
#include "Sprite.h"
#include "Parser.h"

// TODO: Unit
// TODO: Menus
// TODO: Sound
// TODO: Shadows
// TODO: Dialogues
// TODO: Serialization
// TODO: Grid Interaction
// TODO: Change timer to glfw timer

using namespace glm;

int main() {

    // Experimentation code
    auto clock = start_clock();
    auto renderer = create_renderer();
    auto grid = create_grid(renderer);
    auto unit = create_unit();
    all_camera_movement(renderer);
    setup_grid(grid);

    grid->c[3][3]->u = unit;

    Parser p("Scripts/Script.txt");
    p.f = [](Parser* p, std::vector<std::string> s) {
        
    };

    while (p.next())
        std::cout << p.line << std::endl;

    Camera* c = renderer->c;
    c->trns = translate(c->trns, vec3(0, -10, -10));
    c->roll = rotate(c->roll, radians(45.f), vec3(1, 0, 0));
    //

    // Execution code
    renderer->init();

    delete unit;
    do_timer = false;
    clock.join();

    glfwTerminate();
    //

    return 0;
}
