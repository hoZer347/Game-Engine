#version 400

in vec4 fcolor;
in vec2 ftexCoords;

uniform bool type;
uniform sampler2D tex;

out vec4 frag_colour;

void main() {
    if (type)
        frag_colour = texture(tex, ftexCoords);
    else
        frag_colour = fcolor;
};