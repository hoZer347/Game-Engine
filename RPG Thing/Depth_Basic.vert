#version 400

in vec3 vertex;

uniform mat4 light;
uniform mat4 mode;

void main() {
    gl_Position = light * mode * vec4(vertex, 1);
}