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

GLuint mvLoc, projLoc, tfLoc;
glm::mat4 pMatrix, vMatrix, mMatrix, mvMatrix;


void setUpVertices(void)
{

    GLfloat vPositions[] = {
        -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f
    };

    // pyramid with 18 vertices, comprising 6 triangles (four sides, and two on the bottom)
    float pyramidPositions[54] =
    { 
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 
		 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f
    };

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vPositions), vPositions, GL_STATIC_DRAW);
}

void init(GLFWwindow *window) {
    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 8.0f;
    cubeLocX = 0.0f, cubeLocY = -1.0f, cubeLocZ = 0.0f;
    setUpVertices();
}

void display(GLFWwindow *window, Shader *shader, double currentTime) {

    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    shader->UseProgram();

    mvLoc = glGetUniformLocation(shader->program, "mv_matrix");     // get locations of uniforms
    projLoc = glGetUniformLocation(shader->program, "proj_matrix"); // in the shader program

    // build perspective matrix
    glfwGetFramebufferSize(window, &WIDTH_SCREEN, &HEIGHT_SCREEN);
    aspect = (float) WIDTH_SCREEN / (float) HEIGHT_SCREEN;
    pMatrix = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

    mMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-cubeLocX, -cubeLocY, -cubeLocZ));
    mMatrix = glm::rotate(mMatrix, 1.75f, glm::vec3(0.0f, 1.0f, 0.0f));
    vMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mvMatrix = vMatrix * mMatrix; 
    
    // copy pespective and MV matrices to corresponding uniform variables
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMatrix));
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMatrix));

    // Draw the pyramid
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 18);


    mMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-3.0f, 2.0f, 0.0f));
    mvMatrix = vMatrix * mMatrix; 

    // copy pespective and MV matrices to corresponding uniform variables
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMatrix));
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMatrix));
    
    // Draw the cube
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

int main(int argc, char* argv[]) {

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
    Shader draw("/shaders/same.vert", "/shaders/same.frag");
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