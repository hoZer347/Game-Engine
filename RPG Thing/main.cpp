#include <GL/glew.h>
#include <GL/glfw3.h>
#define GLM_FORCE_RADIANS

#include <iostream>

#include "Renderer.h"
#include "Sprite.h"
#include "Text.h"
#include "Grid.h"
#include "RendererActions.h"
#include "GridActions.h"
#include "Dialogue.h"

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
    create_renderer();
    create_grid();

    auto clock = start_clock();
    auto sprite = create_sprite();
    auto unit = create_unit();

    grid_attach_neighbours();
    setup_camera_movement();
    isometric_mount_camera();

    setup_grid();
    //
    
    // Setting up
    unit->s = sprite;
    grid_set(unit, 3, 3);

    bind_texture(sprite);
    //

    // Execution
    init_renderer();

    // Deallocation
    do_timer = false;

    delete RENDERER;

    close_mesh();
    close_text();
    FT_Done_FreeType(lib);

    clock.join();
    //

    return 0;
}
