#version 430  
precision mediump float;
out vec4 color; 
		
void main(void) { 

	if(gl_FragCoord.x < 450) { 
		color = vec4(1.0,0.0,0.0,1.0); 
	} else { 
		color = vec4(0.0,1.0,1.0,1.0);
	}
}