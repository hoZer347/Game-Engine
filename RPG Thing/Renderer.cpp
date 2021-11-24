#include "Renderer.h"

Renderer::Renderer() {
    load();
}

void Renderer::load() {
    // LOADING WINDOW / OPENGL SETTINGS

    glfwInit();

    window = glfwCreateWindow(window_w, window_h, "", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glClearColor(0.5, 0.5, 0.5, 1);

    // Making textures work
    glEnable(GL_TEXTURE_2D);
    //

    // Anti-aliasing
    glEnable(GL_MULTISAMPLE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    //

    // Blocking stuff that are behind opaque objects
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //

    // Alpha processing setup
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);
    //

    // Culling faces that don't face the camera
    glEnable(GL_CULL_FACE);

    // LOADING SHADER BULLSHIT

    create_shader("Shaders/default.vert", "Shaders/default.frag");
    create_shader("Shaders/depth.vert", "Shaders/depth.frag", "Shaders/depth.geom");

    // GENERATING DEPTH BUFFER

    glGenFramebuffers(1, &depth_map);

    // GENERATING VERTEX BUFFER
    
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &_vtxs);
    glBindBuffer(GL_ARRAY_BUFFER, _vtxs);

    glGenBuffers(1, &_inds);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vtxs);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vtx), NULL);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vtx), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vtx), (void*)(7 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // Texture Coordinates
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vtx), (void*)(10 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
}

void Renderer::update() {
    // INITIALIZING WINDOW

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwGetWindowSize(window, &window_w, &window_h);
    glViewport(0, 0, window_w, window_h);

    // DOING MATRIX CALCULATIONS

    c->rotn = c->roll * c->ptch * c->yaww;
    c->mode = c->rotn * c->trns;
    c->view = lookAt(c->eye, c->look, c->up);
    c->proj = perspective(radians(45.0f), (float)window_w/(float)window_h, 0.1f, 100.0f);
    c->norm = transpose(inverse(c->mode));
    c->mvp = c->proj * c->view * c->mode;

    // GENERATING SHADOWS

    glUseProgram(depth_shader);

    // LOADING DEFAULT SHADER

    glUseProgram(shader_programme);

    // LOADING MATRICES

    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mode"), 1, GL_FALSE, value_ptr(c->mode));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "norm"), 1, GL_FALSE, value_ptr(c->norm));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "view"), 1, GL_FALSE, value_ptr(c->view));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "proj"), 1, GL_FALSE, value_ptr(c->proj));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mvp"), 1, GL_FALSE, value_ptr(c->mvp));

    // DRAWING OBJECTS

    for (auto& m : MESH)
        render(m);

    // UNLOADING BUFFERS

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // REFRESHING WINDOW

    glfwSwapBuffers(window);
}

void Renderer::render(Mesh* m) {
    glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
    glBufferData(GL_ARRAY_BUFFER, m->vtxs.size() * sizeof(Vtx), m->vtxs.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->inds.size() * sizeof(unsigned int), m->inds.data(), GL_STATIC_DRAW);

    if (m->ortho)
        glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mode"), 1, GL_FALSE, value_ptr(c->mode * inverse(c->mvp) * m->trns));
    else
        glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mode"), 1, GL_FALSE, value_ptr(c->mode * m->trns));

    // Determining how to draw
    if (m->gl_render_type == GL_LINES)
        glUniform1i(glGetUniformLocation(shader_programme, "type"), 0);
    else if (!m->gl_texture)
        glUniform1i(glGetUniformLocation(shader_programme, "type"), 1);
    else if (m->ortho)
        glUniform1i(glGetUniformLocation(shader_programme, "type"), 2);
    else
        glUniform1i(glGetUniformLocation(shader_programme, "type"), 3);

    // Loading Texture
    glBindTexture(GL_TEXTURE_2D, m->gl_texture);
    glUniform1i(glGetUniformLocation(shader_programme, "tex"), 0);

    // Drawing
    glDrawElements(m->gl_render_type, m->inds.size(), m->gl_data_type, (void*)0);

    // Unloading Texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::create_shader(std::string f1, std::string f2) {
    std::ifstream _v(f1.c_str());
    std::string _vs((std::istreambuf_iterator<char>(_v)),
        std::istreambuf_iterator<char>());

    std::ifstream _f(f2.c_str());
    std::string _fs((std::istreambuf_iterator<char>(_f)),
        std::istreambuf_iterator<char>());

    const char* vertex_shader = _vs.c_str();
    const char* fragment_shader = _fs.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    glUseProgram(shader_programme);
}
void Renderer::create_shader(std::string f1, std::string f2, std::string f3) {
    std::ifstream _v(f1.c_str());
    std::string _vs((std::istreambuf_iterator<char>(_v)),
        std::istreambuf_iterator<char>());

    std::ifstream _f(f2.c_str());
    std::string _fs((std::istreambuf_iterator<char>(_f)),
        std::istreambuf_iterator<char>());

    std::ifstream _g(f3.c_str());
    std::string _gs((std::istreambuf_iterator<char>(_g)),
        std::istreambuf_iterator<char>());

    const char* vertex_shader = _vs.c_str();
    const char* fragment_shader = _fs.c_str();
    const char* geometry_shader = _gs.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    GLuint gs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(gs, 1, &geometry_shader, NULL);
    glCompileShader(gs);

    depth_shader = glCreateProgram();
    glAttachShader(depth_shader, fs);
    glAttachShader(depth_shader, vs);
    glAttachShader(depth_shader, gs);
    glLinkProgram(depth_shader);
    glUseProgram(depth_shader);
}
