#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>

#include "FTL.h"

<<<<<<< HEAD
// Currently doing: Sprite + Timer implementation
=======
#include "Sprite.h"

// Currently doing: Object selection
>>>>>>> 6934b17e924fed4f164fa36a3387acb003af0a0a
// TODO: Add shadows
// TODO: Add sound
// TODO: Sprite Implementation
// TODO: Timer Implementation
// TODO: Find out the normal of a 3D function

using namespace glm;

int main() {
    FT_Init_FreeType(&lib);

    Room* room = create_room();

    auto sprite = create_sprite();
    bind_texture(sprite);

    auto f = create_font();

    auto m1 = create_plane(10, 10);
    auto t = create_text("\nTesting", f);

    change_rendering(m1, GL_LINES);

    for (auto& i : m1->vtxs)
        y_is_negz(i);

    FTL game(room);

    game.init();

    // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}
