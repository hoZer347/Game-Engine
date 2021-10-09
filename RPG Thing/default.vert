#version 400

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoords;

out vec3 fvertex;
out vec4 fcolor;
out vec3 fnormal;
out vec2 ftexCoords;

uniform mat4 mode;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 mvp;

void main() {
    fvertex = vertex;
    fcolor = color;
    fnormal = normal;
    ftexCoords = texCoords;

    gl_Position = mvp * vec4(vertex, 1.0);
}
