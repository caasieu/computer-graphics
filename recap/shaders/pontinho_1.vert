#version 430 
uniform float offset;
	
void main() {	
	
	gl_Position = vec4(offset,0.5,0.0,1.0); 
}