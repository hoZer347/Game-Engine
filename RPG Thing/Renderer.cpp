#include "Renderer.h"

Renderer::Renderer() {
    // LOADING WINDOW / OPENGL SETTINGS

    glfwInit();

    WINDOW = glfwCreateWindow(window_w, window_h, "", NULL, NULL);
    window = WINDOW;
    glfwMakeContextCurrent(window);
    init_inputs(window);

    glfwSwapInterval(1);
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
    glAlphaFunc(GL_GREATER, 0);
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

    mode = glGetUniformLocation(shader_programme, "mode");
    view = glGetUniformLocation(shader_programme, "view");
    proj = glGetUniformLocation(shader_programme, "proj");
    norm = glGetUniformLocation(shader_programme, "norm");
    mvp  = glGetUniformLocation(shader_programme, "mvp");
}

Renderer::~Renderer() {
    delete c;
    delete inputs;
    glfwDestroyWindow(window);
    glDeleteProgram(shader_programme);
    glDeleteProgram(depth_shader);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &_vtxs);
    glDeleteBuffers(1, &_inds);
    glfwTerminate();
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
    c->proj = perspective(
        radians(45.0f),
        (float)window_w/(float)window_h,
        0.1f, 100.0f);
    c->norm = transpose(inverse(c->mode));
    c->mvp = c->proj * c->view * c->mode;

    // GENERATING SHADOWS

    glUseProgram(depth_shader);

    // LOADING DEFAULT SHADER

    glUseProgram(shader_programme);

    // LOADING MATRICES

    glUniformMatrix4fv(mode, 1, GL_FALSE, &c->mode[0][0]);
    glUniformMatrix4fv(view, 1, GL_FALSE, &c->view[0][0]);
    glUniformMatrix4fv(proj, 1, GL_FALSE, &c->proj[0][0]);
    glUniformMatrix4fv(norm, 1, GL_FALSE, &c->norm[0][0]);
    glUniformMatrix4fv(mvp,  1, GL_FALSE, &c->mvp[0][0]);

    // DRAWING OBJECTS

    unsigned int i = 0;

    for (auto& m : MESH)
        if (m)
            render(m);

    // UNLOADING BUFFERS

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // REFRESHING WINDOW

    glfwSwapBuffers(window);
}

void Renderer::init() {
    while (!glfwWindowShouldClose(window)) {
        inputs->update();
        inputs->mouse_ray = get_cam_ray();

        for (auto& m : OBJS)
            if (m && m->animate)
                m->update();

        update();
    }
}

mat2x3 Renderer::get_cam_ray() {
    int w = 0, h = 0;
    glfwGetWindowSize(window, &w, &h);

    vec4 mv = vec4((
        inputs->mx - w / 2) / (w / 2),
        (-inputs->my + h / 2) / (h / 2),
        0, 1);

    Vtx v;

    vec4 eye = mv + vec4(c->eye, 0);
    eye = inverse(c->mvp) * eye;
    eye /= eye.w;
    v.pos = vec3(eye);
    eye = vec4(v.pos, 1);

    vec4 look = mv + vec4(c->look, 0);
    look = inverse(c->mvp) * look;
    look /= look.w;
    v.pos = vec3(look);
    look = vec4(v.pos, 1);

    vec4 ray = (look - eye);
    ray = normalize(ray);

    mat2x3 ret = { vec3(eye), vec3(ray) };

    return ret;
}

void Renderer::render(Mesh* m) {
    if (!m->show)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
    glBufferData(
        GL_ARRAY_BUFFER,
        m->vtxs.size() * sizeof(Vtx),
        m->vtxs.data(),
        GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        m->inds.size() * sizeof(unsigned int),
        m->inds.data(),
        GL_DYNAMIC_DRAW);
    
    mat4 _mode = c->mode * m->trns;

    if (m->ortho) {
        _mode *= inverse(c->mode);
        glUniformMatrix4fv(mode, 1, GL_FALSE, &_mode[0][0]);
    } else
        glUniformMatrix4fv(mode, 1, GL_FALSE, &_mode[0][0]);

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
    GLuint gs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gs, 1, &geometry_shader, NULL);
    glCompileShader(gs);

    depth_shader = glCreateProgram();
    glAttachShader(depth_shader, vs);
    glAttachShader(depth_shader, fs);
    glAttachShader(depth_shader, gs);
    glLinkProgram(depth_shader);
    glUseProgram(depth_shader);
}
