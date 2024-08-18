#include <iostream>
#include <glad/glad.h>
#include "include/classes/Shader.h"
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <filesystem> 

// HardCode a vertex shader
#define numVAOs 1		 // Vertex Array Object
GLuint renderingProgram; //
GLuint vao[numVAOs];
GLuint vao2[numVAOs];

using namespace std;

void init(GLFWwindow *window)
{
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

void display(GLFWwindow *window, double currentTime)
{
	

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int arc, char *argv[])
{
	GLFWwindow *window;

	// initialize the library
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// create windowed mode window and its opengl context
	window = glfwCreateWindow(960, 680, "One - OpenGL", NULL, NULL);
	glfwSwapInterval(1);

	// make the windows context current
	glfwMakeContextCurrent(window);

	// Initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "failed to initialize glad" << endl;
		exit(EXIT_FAILURE);
	}

	init(window);



    // Get the current path of the project
    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path parent_path = current_path.parent_path();
		 	
	Shader pontinho(parent_path.string() + "/shaders/pontinho_1.vert", parent_path.string() + "/shaders/pontinho_1.frag");
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);

	Shader pontinho2(parent_path.string() + "/shaders/pontinho_2.vert", parent_path.string() + "/shaders/pontinho_2.frag");
	glGenVertexArrays(numVAOs, vao2);
	glBindVertexArray(vao2[0]);

	cout << pontinho.program << endl;
	cout << pontinho2.program << endl;

	// loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());

		pontinho.UseProgram();
		glDrawArrays(GL_POINTS, 0, 1);

		pontinho2.UseProgram();
		glDrawArrays(GL_POINTS, 0, 1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
