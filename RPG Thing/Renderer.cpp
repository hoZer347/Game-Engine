#include "Renderer.h"

Renderer::Renderer() {
    load();
}

void Renderer::load() {
    // LOADING WINDOW / OPENGL SETTINGS

    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
    }

    window = glfwCreateWindow(640, 640, "", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    // glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    
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

    // LOADING BUFFERS
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mode"), 1, GL_FALSE, value_ptr(mode));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "view"), 1, GL_FALSE, value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "proj"), 1, GL_FALSE, value_ptr(proj));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mvp"), 1, GL_FALSE, value_ptr(mvp));
}

void Renderer::update() {
    mode = translate(mat4(1.0f), vec3(0, 0, -70));
    view = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
    proj = perspective(radians(100.0f), 1.0f, 0.1f, 100.0f);
    mvp = proj * view * mode;

    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mode"), 1, GL_FALSE, value_ptr(mode));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "view"), 1, GL_FALSE, value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "proj"), 1, GL_FALSE, value_ptr(proj));
    glUniformMatrix4fv(glGetUniformLocation(shader_programme, "mvp"), 1, GL_FALSE, value_ptr(mvp));
}
