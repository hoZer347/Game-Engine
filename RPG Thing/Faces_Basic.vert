#version 400

in vec3 vertex;
in vec2 texCoords;

uniform mat4 trns;

out vec2 ftexCoords;

void main() {
	ftexCoords = texCoords;
	gl_Position = trns * vec4(vertex, 1);
}
