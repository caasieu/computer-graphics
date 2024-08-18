#include <glad/glad.h>

class Shader {
public:
    GLuint program;
    Shader(const GLchar* vertexSource, const GLchar* fragmentSource) {
        
        GLuint vertex = this->createShader(vertexSource, GL_VERTEX_SHADER, "VERTEX");
        GLuint fragment = this->createShader(fragmentSource, GL_FRAGMENT_SHADER, "FRAGMENT");
        this->createProgram(vertex, fragment);
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

    GLuint createProgram(GLuint vertex, GLuint fragment) {

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
