#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "Timer.h"
#include "Grid.h"
#include "Sprite.h"
#include "Text.h"
#include "Unit.h"
#include "UnitMenu.h"
#include "GridActions.h"
#include "RendererActions.h"

// Memory Tracking
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// TODO: Unit
// TODO: Menus
// TODO: Sound
// TODO: Shadows
// TODO: Dialogues
// TODO: Serialization
// TODO: Unit Menu Specifics
// TODO: Make global grid

int main() {
    FT_Init_FreeType(&lib);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Allocation
    auto clock = start_clock();
    auto renderer = create_renderer();
    auto grid = create_grid(renderer, 10, 10);
    auto sprite = create_sprite();
    auto unit = create_unit();
    //

    // Setup
    setup_camera_movement(renderer);
    setup_grid(grid);
    attach_neighbours(grid);
    isometric_mount_camera(renderer);
    
    unit->s = sprite;
    bind_texture(sprite);
    grid->set(unit, 3, 3);
    //

    // Execution
    renderer->init();

    // Deallocation
    do_timer = false;

    delete renderer;
    delete unit;

    close_mesh();
    close_text();
    FT_Done_FreeType(lib);

    clock.join();
    //

    return 0;
}
