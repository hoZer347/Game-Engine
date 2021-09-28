#version 400

in vec3 vertex;
in vec4 color;

out vec4 fcolor;

uniform mat4 mode;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 mvp;

void main() {
    fcolor = color;
    gl_Position = mvp * vec4(vertex, 1.0);
}
