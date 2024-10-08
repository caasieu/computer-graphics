#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/classes/Utils.h"
#include "include/classes/Shader.h"

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

GLuint vLoc, projLoc, tfLoc;
glm::mat4 pMatrix, vMatrix, mMatrix, mvMatrix;
glm::mat4 tMat, rMat, mMat;

void setUpVertices(void)
{

    GLfloat vPositions[] = {
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
        1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
    };

    GLfloat vStripPositions[] = {
        -1.0,
        1.0,
        0.0,
        -1.0,
        -1.0,
        0.0,
        1.0,
        -1.0,
        0.0, // 1 triangle
        1.0,
        1.0,
        0.0,
    };

    GLfloat vColors[] = {
        0.5, 0.0, 0.0, 0.5, 0.0, 0.0, 0.5, 0.0, 0.0, // primeira face (front)
        0.5, 0.0, 0.0, 0.5, 0.0, 0.0, 0.5, 0.0, 0.0, //

        0.0, 0.5, 0.0, 0.0, 0.5, 0.0, 0.0, 0.5, 0.0, // segunda face (right)
        0.0, 0.5, 0.0, 0.0, 0.5, 0.0, 0.0, 0.5, 0.0, // segunda face (right)

        0.5, 0.5, 0.0, 0.5, 0.5, 0.0, 0.5, 0.5, 0.0, // terceira face (top)
        0.5, 0.5, 0.0, 0.5, 0.5, 0.0, 0.5, 0.5, 0.0, //

        0.0, 0.5, 0.5, 0.0, 0.5, 0.5, 0.0, 0.5, 0.5, // terceira face (left)
        0.0, 0.5, 0.5, 0.0, 0.5, 0.5, 0.0, 0.5, 0.5, // terceira face (left)

        0.5, 0.0, 0.5, 0.5, 0.0, 0.5, 0.5, 0.0, 0.5, // quarta face (bottom)
        0.5, 0.0, 0.5, 0.5, 0.0, 0.5, 0.5, 0.0, 0.5, // quarta face (bottom)

    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(2, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vPositions), vPositions, GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vColors), vColors, GL_STATIC_DRAW);
}

void init(GLFWwindow *window)
{

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 420.0f; // cameraZ = 420.0f;
    cubeLocX = 0.0f, cubeLocY = -2.0f, cubeLocZ = 0.0f;
    setUpVertices();
}

float fps = 0.005f;
void display(GLFWwindow *window, Shader *shader, double currentTime)
{
    // cameraX += fps, cameraY += -fps;

    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    shader->UseProgram();

    vLoc = glGetUniformLocation(shader->program, "v_matrix");     // get locations of uniforms
    projLoc = glGetUniformLocation(shader->program, "proj_matrix"); // in the shader program


    // build perspective matrix
    glfwGetFramebufferSize(window, &WIDTH_SCREEN, &HEIGHT_SCREEN);
    aspect = (float)WIDTH_SCREEN / (float)HEIGHT_SCREEN;
    pMatrix = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
    vMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

    timeFactor = ((float) currentTime);
    tfLoc = glGetUniformLocation(shader->program, "tf");
    glUniform1f(tfLoc, (float) timeFactor);


    // copy pespective and MV matrices to corresponding uniform variables
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMatrix));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMatrix));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // adjust opengl settings and draw model
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 300000);
    
}

int main(int argc, char *argv[])
{

    GLFWwindow *window;
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "Drawing - RECAP", NULL, NULL);
    glfwSwapInterval(1);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        exit(EXIT_FAILURE);

    // My drawing-shader
    Shader draw("/shaders/draw_instancing.vert", "/shaders/draw.frag");
    init(window);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        display(window, &draw, glfwGetTime());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}