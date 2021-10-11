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
    
    // LOADING SHADER BULLSHIT

    create_shader("default.vert", "default.frag");
    create_shader("depth.vert", "depth.frag", "depth.geom");

    // GENERATING DEPTH BUFFER

    glGenFramebuffers(1, &depth_map);

    // GENERATING VERTEX BUFFER
    
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &_inds);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

    glGenBuffers(1, &_vtxs);
    glBindBuffer(GL_ARRAY_BUFFER, _vtxs);

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

    c.proj = perspective(radians(45.0f), (float)window_w/(float)window_h, 0.1f, 100.0f);
    c.norm = transpose(inverse(c.mode));
    c.mvp = c.proj * c.view * c.mode;

    // GENERATING SHADOWS

    glUseProgram(depth_shader);

    // DRAWING VERTICES

    glUseProgram(shader_programme);

    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mode"), 1, GL_FALSE, value_ptr(c.mode));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "norm"), 1, GL_FALSE, value_ptr(c.norm));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "view"), 1, GL_FALSE, value_ptr(c.view));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "proj"), 1, GL_FALSE, value_ptr(c.proj));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mvp"), 1, GL_FALSE, value_ptr(c.mvp));

    glUniform1i(glGetUniformLocation(shader_programme, "type"), GL_FALSE);

    glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

    glBufferData(GL_ARRAY_BUFFER, vtxs.size() * sizeof(Vtx), vtxs.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(GLuint), inds.data(), GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, NULL);

    // DRAWING TEXTURES

    glUniform1i(glGetUniformLocation(shader_programme, "type"), GL_TRUE);

    glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

    glBufferData(GL_ARRAY_BUFFER, texs.size() * sizeof(Vtx), texs.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tnds.size() * sizeof(GLuint), tnds.data(), GL_STATIC_DRAW);

    glDrawElements(GL_QUADS, tnds.size(), GL_UNSIGNED_INT, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // REFRESHING WINDOW

    glfwSwapBuffers(window);
}

void Renderer::add(std::string file_name) {
    texture = SOIL_load_OGL_texture(file_name.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glUniform1i(glGetUniformLocation(shader_programme, "tex"), num_texs);

    num_texs++;
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
