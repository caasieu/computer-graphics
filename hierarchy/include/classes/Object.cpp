#include "Object.hpp"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Object::Object(Shader * n_shader, float * n_positions, int n_size, GLuint n_vbo_index) {
    this->vbo_index = n_vbo_index;
    this->positions = n_positions;
    this->size = n_size;
    this->offset = size / 3;
    this->shader = n_shader; 

    std::cout<<"vbo_index = "<< vbo_index <<std::endl;
    std::cout<<"size ="<< size <<" : offset = "<< this->offset <<std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, vbo_index);
    glBufferData(GL_ARRAY_BUFFER, size  * sizeof(float), positions, GL_STATIC_DRAW);

}

void Object::draw(GLenum primitives, const glm::mat4& n_mv, const glm::mat4& n_proj) {
    shader->UseProgram();

    this->mv_loc = glGetUniformLocation(shader->program, "mv_matrix");     // get locations of uniforms
    this->proj_loc = glGetUniformLocation(shader->program, "proj_matrix"); // in the shader program
    
    glUniformMatrix4fv(mv_loc, 1, GL_FALSE, glm::value_ptr(n_mv));
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(n_proj));

    // Draw the pyramid
    glBindBuffer(GL_ARRAY_BUFFER, vbo_index);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(primitives, 0, this->offset); // this->offset);
}

Object::~Object() {
    // deleting VBOs
    glDeleteBuffers(1, &vbo_index);
}