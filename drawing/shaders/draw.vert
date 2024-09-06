#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertex_color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec3 sent_color;

void main(void) {
    sent_color = vertex_color;
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
}