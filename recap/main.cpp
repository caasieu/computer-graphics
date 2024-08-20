#include <iostream>
#include <glad/glad.h>
#include "include/classes/Shader.h"
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <filesystem>
#include "include/classes/Utils.h"

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

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
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

	// Get the current path of the project
	std::filesystem::path current_path = std::filesystem::current_path();
	std::filesystem::path parent_path = current_path.parent_path();


	float x = 0.0f;
	float inc = 0.01f;

	Shader pontinho(parent_path.string() + "/shaders/pontinho_1.vert", parent_path.string() + "/shaders/pontinho_1.frag");
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);

	Shader pontinho2(parent_path.string() + "/shaders/pontinho_2.vert", parent_path.string() + "/shaders/pontinho_2.frag");
	glGenVertexArrays(numVAOs, vao2);
	glBindVertexArray(vao2[0]);

	Utils::checkOpenGLError();

	//float allowed_size = 0.0f;
	//glGetFloatv(GL_POINT_SIZE_RANGE, &allowed_size);
	//cout<<"maximum allowed size for a point:" << allowed_size << endl;

	cout << pontinho.program << endl;
	cout << pontinho2.program << endl;


	// point size increase
	float point_size = 1.0f;
	float point_size_inc = 1.0f;

	// loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{

		glPointSize(point_size);
		display(window, glfwGetTime());
		

		pontinho.UseProgram();


		point_size += point_size_inc;
		if(point_size > 50.0f) point_size_inc = -0.5f;
		if(point_size < -50.0f) point_size_inc = 0.5f;


		x += inc;
		if(x > 0.95f) inc = -0.01f;
		if(x < -0.95f) inc = 0.01f;
		GLuint offsetLoc = glGetUniformLocation(pontinho.program, "offset");
		glProgramUniform1f(pontinho.program, offsetLoc, x);
		glDrawArrays(GL_POINTS, 0, 1);

		pontinho2.UseProgram();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
