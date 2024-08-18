#include <iostream>
#include <glad/glad.h>
#include <sstream>
#include <fstream>  


// A simple class i created to facilitate creating my shaders, programs for multiple objects
class Shader
{
public:
    GLuint program;
    Shader(const std::string &vPath, const std::string &fPath)
    {
        std::string vertexSource = this->loadSource(vPath);
        std::string fragmentSource = this->loadSource(fPath);

        GLuint vertex = this->createShader(vertexSource.c_str(), GL_VERTEX_SHADER, "VERTEX");
        GLuint fragment = this->createShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER, "FRAGMENT");
        this->createProgram(vertex, fragment);

    }

    // loads the program containing the shaders into the opengl pipeline stages (onto the GPU)
    void UseProgram()
    {
        glUseProgram(this->program);
    }

private:
    GLuint createShader(const GLchar *source, GLenum type, const GLchar *type_src)
    {

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        this->checkCompileErrors(shader, type_src); //"VERTEX" | FRAGMENT

        return shader;
    }

    std::string loadSource(const std::string& path)
    {
        std::ifstream in(path);
        std::stringstream buffer;
        buffer << in.rdbuf();
        return buffer.str();
        
    }

    GLuint createProgram(GLuint vertex, GLuint fragment)
    {

        this->program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);

        this->checkLinkingErrors(program);

        return program;
    }

    void checkLinkingErrors(GLuint program)
    {
        GLint success;
        GLchar infoLog[1024];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    void checkCompileErrors(GLuint shader, const GLchar *type)
    {
        GLint success;
        GLchar infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
};
