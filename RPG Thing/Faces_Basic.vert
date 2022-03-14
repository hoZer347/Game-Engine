#version 400

in vec3 vertex;
in vec2 texCoords;

out vec2 ftexCoords;

void main() {
	ftexCoords = texCoords;
	gl_Position = vec4(vertex, 1);
}
