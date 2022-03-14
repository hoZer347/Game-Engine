#version 400

in vec2 ftexCoords;

uniform sampler2D tex;

void main() {
    gl_FragColor = texture(tex, ftexCoords);
}
