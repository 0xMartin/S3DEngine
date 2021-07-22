#include "shader.h"


ShaderProgram::ShaderProgram() {
    ShaderProgram::ID = glCreateProgram();
}

void ShaderProgram::use() {
    glUseProgram(ID);
}

void ShaderProgram::link() {
    int success;
    char infoLog[512];

    glLinkProgram(ShaderProgram::ID);

    //print linking errors if any
    glGetProgramiv(ShaderProgram::ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << __FUNCTION__ << " : linking failed [" <<
                     ShaderProgram::ID << "]\n" << infoLog << std::endl;
    }
}

void ShaderProgram::addShader(const GLchar * source, GLenum type) {
    if(source == NULL) {
        std::cerr << __FUNCTION__ << ": source is NULL [" <<
                     ShaderProgram::ID << "]\n";
        return;
    }

    if(type != GL_COMPUTE_SHADER &&
            type != GL_VERTEX_SHADER &&
            type != GL_TESS_CONTROL_SHADER &&
            type != GL_TESS_EVALUATION_SHADER &&
            type != GL_GEOMETRY_SHADER &&
            type != GL_FRAGMENT_SHADER) {
        std::cerr << __FUNCTION__ << ": type of shader is unknown [" <<
                     ShaderProgram::ID << "]" << std::endl;
        return;
    }

    //create shader and compile
    GLuint shader_ID = glCreateShader(type);
    glShaderSource(shader_ID, 1, &source, NULL);
    glCompileShader(shader_ID);

    //print compile errors if any
    int success;
    char infoLog[512];
    glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader_ID, 512, NULL, infoLog);
        std::cout << __FUNCTION__ << " : compilation failed [" <<
                     ShaderProgram::ID << "]\n" << infoLog << std::endl;
    };

    //attach shader to shader program
    ShaderProgram::shaders.push_back(shader_ID);
    glAttachShader(ShaderProgram::ID, shader_ID);

    glDeleteShader(shader_ID);
}

void ShaderProgram::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(
                    ShaderProgram::ID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string &name, GLint value) {
    glUniform1i(glGetUniformLocation(
                    ShaderProgram::ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, GLfloat value) {
    glUniform1f(glGetUniformLocation(
                    ShaderProgram::ID, name.c_str()), value);
}

void ShaderProgram::setMatrix4(const std::string &name, const GLfloat * value) {
    glUniformMatrix4fv(glGetUniformLocation(
                           ShaderProgram::ID, name.c_str()), 1, GL_FALSE, value);
}
