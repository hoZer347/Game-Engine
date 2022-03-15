#version 450

layout(points) in;
layout(triangle_strip, max_vertices=6) out;

uniform vec2 start  = vec2(0);
uniform vec2 stride = vec2(1);
uniform mat4 mvp    = mat4(1);
uniform mat4 trns   = mat4(1);

out vec2 ftexCoords;

void main() {
    float x1 = start.x, y1 = start.y;
    float x2 = stride.x, y2 = stride.y;

    mat4 m = mvp * trns;

    vec4
        p00 = m * (gl_in[0].gl_Position + vec4(0, 0, 0, 0)),
        p10 = m * (gl_in[0].gl_Position + vec4(1, 0, 0, 0)),
        p01 = m * (gl_in[0].gl_Position + vec4(0, 1, 0, 0)),
        p11 = m * (gl_in[0].gl_Position + vec4(1, 1, 0, 0));

    ftexCoords = vec2(x1, y1);
    gl_Position = p00;
    EmitVertex();

    ftexCoords = vec2(x1 + x2, y1);
    gl_Position = p10;
    EmitVertex();

    ftexCoords = vec2(x1 + x2, y1 + y2);
    gl_Position = p11;
    EmitVertex();

    ftexCoords = vec2(x1, y1);
    gl_Position = p00;
    EmitVertex();

    ftexCoords = vec2(x1, y1 + y2);
    gl_Position = p01;
    EmitVertex();

    ftexCoords = vec2(x1 + x2, y1 + y2);
    gl_Position = p11;
    EmitVertex();

    EndPrimitive();
}
