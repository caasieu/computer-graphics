#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/classes/Utils.h"
#include "include/classes/Shader.h"


int main(int argc, char * argv[]) {

    GLFWwindow* window;
    if(!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    window = glfwCreateWindow(640, 480, "Drawing - RECAP", NULL, NULL);
    glfwSwapInterval(1);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) exit(EXIT_FAILURE);


    // My drawing-shader
    Shader draw("/shaders/draw.vert", "/shaders/draw.frag");
    
    GLuint numVAOs = 1;
    GLuint vao[numVAOs];
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);


    while(!glfwWindowShouldClose(window)) {

        glPointSize(30.0f);
        Utils::initWindow();

        draw.UseProgram();
        glDrawArrays(GL_POINTS, 0, 1);

        glfwSwapBuffers(window);      
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}