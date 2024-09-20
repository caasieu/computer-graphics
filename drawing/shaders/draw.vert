#version 430 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 vertex_color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

//out vec3 sent_color;
out vec4 varyingColor;

void main(void) {
    //sent_color = vertex_color;
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
}