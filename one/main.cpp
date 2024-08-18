#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
using namespace std;

void init(GLFWwindow* window) {
	if(!window) { 
		glfwTerminate();
	 	exit(EXIT_FAILURE);
	}
}

void display(GLFWwindow* window, double currentTime) {
	glClearColor(1.0, 0.5, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


int main(int arc, char * argv[]) {
	GLFWwindow * window;

	// initialize the library
	if(!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	

	// create windowed mode window and its opengl context
	window = glfwCreateWindow(640, 480, "One - OpenGL", NULL, NULL);
	glfwSwapInterval(1);
	init(window);	
	
	// make the windows context current
	glfwMakeContextCurrent(window);

	// Initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
		cout<< "failed to initialize glad"<<endl; 
		exit(EXIT_FAILURE); 
	}

	// loop until the user closes the window 
	while(!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
