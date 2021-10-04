#version 400

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoords;

out vec4 fcolor;
out vec2 ftexCoords;

uniform mat4 mode;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 mvp;

void main() {
    fcolor = color;
    ftexCoords = texCoords;
    gl_Position = mvp * vec4(vertex, 1.0);
}
