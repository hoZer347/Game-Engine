#version 450 core

in vec3 v;

void main() {
	gl_Position = vec4(v, 1);
};
