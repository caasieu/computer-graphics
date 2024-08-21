#include "include/classes/Utils.h"

#include <iostream>
#include <glad/glad.h>

bool Utils::checkOpenGLError(){
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        std::cout << "glError: " << glErr << std::endl;
        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}