#version 400

layout(points) in;
layout(triangle_strip, max_vertices=6) out;

uniform vec2 start = vec2(0);
uniform vec2 stride = vec2(1);

out vec2 ftexCoords;

void main() {
    float x1 = start.x, y1 = start.y;
    float x2 = stride.x, y2 = stride.y;

    ftexCoords = vec2(x1, y1);
    gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
    EmitVertex();

    ftexCoords = vec2(x1 + x2, y1);
    gl_Position = gl_in[0].gl_Position + vec4(1, 0, 0, 0);
    EmitVertex();

    ftexCoords = vec2(x1 + x2, y1 + y2);
    gl_Position = gl_in[0].gl_Position + vec4(1, 1, 0, 0);
    EmitVertex();

    ftexCoords = vec2(x1, y1);
    gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
    EmitVertex();

    ftexCoords = vec2(x1, y1 + y2);
    gl_Position = gl_in[0].gl_Position + vec4(0, 1, 0, 0);
    EmitVertex();

        ftexCoords = vec2(x1 + x2, y1 + y2);
    gl_Position = gl_in[0].gl_Position + vec4(1, 1, 0, 0);
    EmitVertex();

    EndPrimitive();
}
