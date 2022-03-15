#version 450

layout(points) in;
layout(triangle_strip, max_vertices=6) out;

out vec2 ftexCoords;

uniform mat4 trns;
uniform mat4 mvp;

void main() {
    mat4 m = mvp * trns;

    vec4
        p00 = m * (gl_in[0].gl_Position + vec4(0, 0, 0, 0)),
        p10 = m * (gl_in[0].gl_Position + vec4(1, 0, 0, 0)),
        p01 = m * (gl_in[0].gl_Position + vec4(0, 1, 0, 0)),
        p11 = m * (gl_in[0].gl_Position + vec4(1, 1, 0, 0));

    ftexCoords = vec2(0, 0);
    gl_Position = p00;
    EmitVertex();

    ftexCoords = vec2(1, 0);
    gl_Position = p10;
    EmitVertex();

    ftexCoords = vec2(1, 1);
    gl_Position = p11;
    EmitVertex();

    ftexCoords = vec2(0, 0);
    gl_Position = p00;
    EmitVertex();

    ftexCoords = vec2(0, 1);
    gl_Position = p01;
    EmitVertex();

    ftexCoords = vec2(1, 1);
    gl_Position = p11;
    EmitVertex();

    EndPrimitive();
}
