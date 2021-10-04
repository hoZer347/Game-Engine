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

    std::ifstream _v("default.vert");
    std::string _vs((std::istreambuf_iterator<char>(_v)),
        std::istreambuf_iterator<char>());

    std::ifstream _f("default.frag");
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

    // GENERATING VERTEX BUFFER
    
    glGenBuffers(1, &_inds);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

    glGenBuffers(1, &_vtxs);
    glBindBuffer(GL_ARRAY_BUFFER, _vtxs);

    // Vertex Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //// GENERATING TEXTURE BUFFERS

    //glGenBuffers(1, &_texs);
    //glBindBuffer(GL_ARRAY_BUFFER, _texs);

    //glGenBuffers(1, &_tnds);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _tnds);

    //// Texture Position
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
    //glEnableVertexAttribArray(2);

    //glGenBuffers(1, &_cdss);
    //glBindBuffer(GL_ARRAY_BUFFER, _cdss);

    //glGenBuffers(1, &_cnds);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _cnds);

    //// Texture Coordinates
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(3);
}

void Renderer::update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);

    glfwGetWindowSize(window, &window_w, &window_h);
    glViewport(0, 0, window_w, window_h);

    c.proj = perspective(radians(45.0f), (float)window_w/(float)window_h, 0.1f, 100.0f);
    
    c.mvp = c.proj * c.view * c.mode;

    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mode"), 1, GL_FALSE, value_ptr(c.mode));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "view"), 1, GL_FALSE, value_ptr(c.view));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "proj"), 1, GL_FALSE, value_ptr(c.proj));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mvp"), 1, GL_FALSE, value_ptr(c.mvp));

    // DRAWING VERTICES

    glBindBuffer(GL_ARRAY_BUFFER, _vtxs);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _inds);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(GLuint), inds.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vtxs.size() * sizeof(Vtx), vtxs.data(), GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, NULL);

    // DRAWING TEXTURES

    glfwSwapBuffers(window);
}

void Renderer::add(std::string file_name) {
    int img_w=0, img_h=0;
    unsigned char* img = SOIL_load_image(file_name.c_str(), &img_w, &img_h, NULL, NULL);

    glBindTexture(GL_TEXTURE_2D, num_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img_w, img_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

    SOIL_free_image_data(img);

    num_tex++;
}
