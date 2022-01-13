#include <GL/glew.h>
#include <GL/glfw3.h>
#define GLM_FORCE_RADIANS

#include <iostream>

#include "Renderer.h"
#include "Sprite.h"
#include "Text.h"
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
    auto clock = start_clock();
    auto renderer = create_renderer();
    auto sprite = create_sprite();
    auto dialogue = create_dialogue(renderer);
    //
    
    bind_texture(sprite);
    //

    // Execution
    renderer->init();

    // Deallocation
    do_timer = false;

    delete renderer;

    close_mesh();
    close_text();
    FT_Done_FreeType(lib);

    clock.join();
    //

    return 0;
}
