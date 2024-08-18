#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int initialize_window() {
    GLFWwindow * window;

	// initialize the library
	if(!glfwInit())
		return -1;

	// create windowed mode window and its opengl context
	window = glfwCreateWindow(640, 480, "One - OpenGL", NULL, NULL);
	if(!window) { 
		glfwTerminate();
		return -1;
	}

	// make the windows context current
	glfwMakeContextCurrent(window);

	// Initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
		std::cout<< "failed to initialize glad"<<std::endl; 
		return -1; 
	}

}

