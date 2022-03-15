#version 450

in vec2 ftexCoords;

layout (binding = 0) uniform sampler2D tex1;
layout (binding = 1) uniform sampler2D depth_map;

uniform mat4 lightMat;

void main() {
    gl_FragColor = texture(tex1, ftexCoords) * texture(depth_map, ftexCoords);
}
