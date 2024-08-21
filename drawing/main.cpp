#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/classes/Utils.h"


int main(int argc, char * argv[]) {

    GLFWwindow* window;
    if(!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    window = glfwCreateWindow(640, 480, "Drawing - RECAP", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) exit(EXIT_FAILURE);

    while(!glfwWindowShouldClose(window)) {

        glfwSwapBuffers(window);      
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}