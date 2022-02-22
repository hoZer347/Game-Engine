#include "Shader.h"

// External Library Includes
#include "GLFW/glew.h"
#include "GLFW/glfw3.h"


#include <fstream>

namespace Shader {
    unsigned int shader_programme = 0;

	void add(const char* file_name) {

	}

	void link() {

	}

    void create_shader(std::string f1, std::string f2) {
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
}
