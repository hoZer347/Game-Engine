#version 450

in vec2 ftexCoords;
in vec4 fcolor;

layout (binding = 0) uniform sampler2D tex1;

void main() {
    gl_FragColor = texture(tex1, ftexCoords) * fcolor;
}
