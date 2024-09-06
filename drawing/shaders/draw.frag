#version 430 core

precision mediump float;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

in vec3 sent_color;
out vec4 color;

void main(void) {
    color = vec4(sent_color, 1.0);
}