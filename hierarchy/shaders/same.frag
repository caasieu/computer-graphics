#version 430 core
precision mediump float;

in vec4 varyingColor;
out vec4 color;

void main(void) {
    color = varyingColor; 
}