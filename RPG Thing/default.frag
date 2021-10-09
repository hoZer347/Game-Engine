#version 400

in vec3 fvertex;
in vec4 fcolor;
in vec3 fnormal;
in vec2 ftexCoords;

uniform sampler2D tex;
uniform bool type;

out vec4 frag_colour;

void main() {
	if (type)
		frag_colour = texture2D(tex, ftexCoords);
	else
		frag_colour = fcolor;
};