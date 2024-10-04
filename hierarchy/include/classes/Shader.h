#ifndef SHADER_H    // Check if SHADER_H is not defined
#define SHADER_H    // Define SHADER_H


#include <iostream>
#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <filesystem>

// A simple class i created to facilitate creating my shaders, programs for multiple objects
class Shader
{
public:
    GLuint program;
    Shader(const std::string &vPath, const std::string &fPath)
    {

	    // Get the current path of the project
	    std::filesystem::path current_path = std::filesystem::current_path();
	    std::filesystem::path parent_path = current_path.parent_path();

        std::string vertexSource = this->loadSource(parent_path.string() + vPath);
        std::string fragmentSource = this->loadSource(parent_path.string() + fPath);

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

    std::string loadSource(const std::string &path)
    {
        std::ifstream in(path);
        std::stringstream buffer;
        buffer << in.rdbuf();
        return buffer.str();
    }

    // 2nd optional function to read the source code of shaders in a text file
    std::string readShaderSource(const char *filePath)
    {
        std::string content;
        std::ifstream fileStream(filePath, std::ios::in);
        std::string line = "";
        while (!fileStream.eof())
        {
            getline(fileStream, line);
            content.append(line + "\n");
        }
        fileStream.close();
        return content;
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
                      << infoLog << "\n -- " << std::endl;
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
                      << infoLog << "\n -- " << std::endl;
        }
    }
};


#endif