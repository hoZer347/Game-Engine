#version 400

in vec3 vertex;
in vec2 texCoords;

out vec2 ftexCoords;

uniform mat4 light = mat4(1);
uniform mat4 mode  = mat4(1);

void main() {
    ftexCoords = texCoords;
    gl_Position = light * mode * vec4(vertex, 1);
}