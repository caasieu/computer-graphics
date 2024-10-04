#include "Shader.h"

#ifndef OBJECT_H
#define OBJECT_H
#include <glad/glad.h>
#include <glm/glm.hpp>

// for these examples i want to have a unique projection and model-view matrix 
// for every object, it might simplify things by a lot

class Object {
    public:
        Object(Shader * n_shader, float * n_positions, int n_size = 0, GLuint n_vbo_index = 0);
        ~Object();

        // Variables
        //glm::mat4 proj_matrix;
        //glm::mat4 mv_matrix;

        int size, offset; GLuint vbo_index, proj_loc, mv_loc;
        float* positions; Shader * shader;

        void draw(GLenum primitives, const glm::mat4& n_mv, const glm::mat4& n_proj);
};

#endif