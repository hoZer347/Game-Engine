#include "Shaders.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include <unordered_map>
#include <fstream>
#include <string>

#include <iostream>

namespace shader {
    std::unordered_map<const char*, unsigned int> shaders;

    unsigned int create(const char* file_name) {
        if (shaders[file_name])
            return shaders[file_name];

        unsigned int shader = glCreateProgram();

        std::string f = file_name;

        GLuint
            vs = glCreateShader(GL_VERTEX_SHADER),
            gs = glCreateShader(GL_GEOMETRY_SHADER),
            fs = glCreateShader(GL_FRAGMENT_SHADER);

        // .vert
        std::ifstream _v(f + ".vert");
        if (_v.good()) {
            std::string _vs((std::istreambuf_iterator<char>(_v)),
                std::istreambuf_iterator<char>());
            const char* vert_shader = _vs.c_str();
            glShaderSource(vs, 1, &vert_shader, NULL);
            glCompileShader(vs);
            glAttachShader(shader, vs);
        }

        // .geom
        std::ifstream _g(f + ".geom");
        if (_g.good()) {
            std::string _gs((std::istreambuf_iterator<char>(_g)),
                std::istreambuf_iterator<char>());
            const char* geom_shader = _gs.c_str();
            glShaderSource(gs, 1, &geom_shader, NULL);
            glCompileShader(gs);
            glAttachShader(shader, gs);
        }

        // .frag
        std::ifstream _f(f + ".frag");
        if (_f.good()) {
            std::string _fs((std::istreambuf_iterator<char>(_f)),
                std::istreambuf_iterator<char>());
            const char* frag_shader = _fs.c_str();
            glShaderSource(fs, 1, &frag_shader, NULL);
            glCompileShader(fs);
            glAttachShader(shader, fs);
        }

        glLinkProgram(shader);

        shaders[f.c_str()] = shader;

        return shader;
    }
}
