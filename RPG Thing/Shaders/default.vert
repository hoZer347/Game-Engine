#version 400

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoords;

out vec3 fvertex;
out vec4 fcolor;
out vec3 fnormal;
out vec2 ftexCoords;

out vec3 lightPos;

uniform mat4 mode;
uniform mat4 norm;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 mvp;

uniform vec3 L=vec3(100, 100, 100);

void main() {
    lightPos = vec3(mode * vec4(L, 1));
    vec4 vertPos4 = view * mode * vec4(vertex, 1.0);
    fvertex = vec3(vertPos4) / vertPos4.w;
    fcolor = color;
    fnormal = vec3(norm * vec4(normal, 0.0));
    ftexCoords = texCoords;

    gl_Position = proj * vertPos4;
}
