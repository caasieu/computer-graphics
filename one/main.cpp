#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>

// HardCode a vertex shader
#define numVAOs 1		 // Vertex Array Object
GLuint renderingProgram; //
GLuint vao[numVAOs];

using namespace std;

GLuint createShaderProgram();
void checkCompileErrors(GLuint shader, const std::string& type);
void checkLinkingErrors(GLuint program);

void init(GLFWwindow *window)
{
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

}

void display(GLFWwindow *window, double currentTime)
{

	glUseProgram(renderingProgram);

	glClearColor(1.0, 0.5, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_POINTS, 0, 1);
}

GLuint createShaderProgram() {
	const GLchar *vshaderSource = R"END(
		#version 430 

		void main() {	
			gl_Position = vec4(0.0,0.0,0.0,1.0); 
		}
	)END";

	const GLchar *fshaderSource = R"END(
		#version 430  
		precision mediump float;
		out vec4 color; 
		
		void main() { 
			color = vec4(0.0,1.0,0.0,1.0);
		}
	)END";
	


	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
		
	glCompileShader(vShader);
    checkCompileErrors(vShader, "VERTEX");
	glCompileShader(fShader);
    checkCompileErrors(fShader, "FRAGMENT");

	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
    checkLinkingErrors(vfProgram);

	return vfProgram;
}

void checkCompileErrors(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

void checkLinkingErrors(GLuint program)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
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
	init(window);

	// make the windows context current
	glfwMakeContextCurrent(window);

	// Initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "failed to initialize glad" << endl;
		exit(EXIT_FAILURE);
	}


	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);

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
