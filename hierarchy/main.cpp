#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/classes/Utils.h"
#include "include/classes/Shader.h"
#include "include/classes/Object.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define numVAOs 1
#define numVBOs 2
GLuint vao[numVAOs], vbo[numVBOs];

int WIDTH_SCREEN = 1240;
int HEIGHT_SCREEN = 640;

float aspect, timeFactor;
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;

GLuint mvLoc, projLoc, tfLoc;
glm::mat4 pMatrix, vMatrix, mMatrix, mvMatrix;

GLfloat cubePositions[] = {
    -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f};

// pyramid with 18 vertices, comprising 6 triangles (four sides, and two on the bottom)
float pyramidPositions[54] =
    {
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f};

void setUpVertices(void)
{

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);
}

void init(GLFWwindow *window)
{
    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 8.0f;
    cubeLocX = 0.0f, cubeLocY = -1.0f, cubeLocZ = 0.0f;
    setUpVertices();
}

void calculate(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &WIDTH_SCREEN, &HEIGHT_SCREEN);
    aspect = (float)WIDTH_SCREEN / (float)HEIGHT_SCREEN;
    pMatrix = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

    mMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-cubeLocX, -cubeLocY, -cubeLocZ));
    mMatrix = glm::rotate(mMatrix, 1.75f, glm::vec3(0.0f, 1.0f, 0.0f));
    vMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mvMatrix = vMatrix * mMatrix;
}


int main(int argc, char *argv[])
{

    GLFWwindow *window;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "Multiple - RECAP", NULL, NULL);
    glfwSwapInterval(1);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        exit(EXIT_FAILURE);

    // My drawing-shader
    init(window);
    Shader draw("/shaders/same.vert", "/shaders/same.frag");
    Object pyramid(&draw, pyramidPositions, sizeof(pyramidPositions) / sizeof(pyramidPositions[0]), vbo[0]);
    Object cube(&draw, cubePositions, sizeof(cubePositions) / sizeof(cubePositions[0]), vbo[1]);


    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        // display(window, &draw, glfwGetTime());

        calculate(window);
        pyramid.draw(GL_TRIANGLES, mvMatrix, pMatrix);

        mMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-3.0f, 2.0f, 0.0f));
        mvMatrix = vMatrix * mMatrix;
        cube.draw(GL_TRIANGLES, mvMatrix, pMatrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}