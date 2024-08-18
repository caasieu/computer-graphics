#include <iostream>
#include <glad/glad.h>
#include "include/classes/Shader.h"
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>

// HardCode a vertex shader
#define numVAOs 1		 // Vertex Array Object
GLuint renderingProgram; //
GLuint vao[numVAOs];
GLuint vao2[numVAOs];


using namespace std;



const GLchar *vshaderSource = R"END(
	#version 430 
	
	void main() {	
		gl_Position = vec4(0.5,0.5,0.0,1.0); 
	}
)END";


const GLchar *vshaderSource2 = R"END(
	#version 430 
	
	void main() {	
		gl_Position = vec4(-0.5,-0.5,0.0,1.0); 
	}
)END";

const GLchar *fshaderSource = R"END(
	#version 430  
	precision mediump float;
	out vec4 color; 
		
	void main() { 
		color = vec4(0.0,1.0,1.0,1.0);
	}
)END";

const GLchar *fshaderSource2 = R"END(
	#version 430  
	precision mediump float;
	out vec4 color; 
		
	void main() { 
		color = vec4(1.0,0.0,1.0,1.0);
	}
)END";


void init(GLFWwindow *window)
{
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}	


}

void display(GLFWwindow *window, double currentTime)
{

	//glUseProgram(renderingProgram);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);




	Shader pontinho(vshaderSource, fshaderSource);    
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_POINTS, 0, 1);

	Shader pontinho2(vshaderSource2, fshaderSource2);    
	glGenVertexArrays(numVAOs, vao2);
	glBindVertexArray(vao2[0]);
	glDrawArrays(GL_POINTS, 0, 1);

}



int main(int arc, char *argv[])
{
	GLFWwindow *window;

	// initialize the library
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// create windowed mode window and its opengl context
	window = glfwCreateWindow(960, 680, "One - OpenGL", NULL, NULL);
	glfwSwapInterval(1);
	
	// make the windows context current
	glfwMakeContextCurrent(window);

	// Initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "failed to initialize glad" << endl;
		exit(EXIT_FAILURE);
	}

	init(window);


	// loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
