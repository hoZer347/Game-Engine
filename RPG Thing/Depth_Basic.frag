#version 400

in vec2 ftexCoords;

uniform sampler2D tex;

void main() {
    vec4 v = vec4(vec3(1) - texture(tex, ftexCoords).xyz, 1);

    gl_FragColor = v;
};
