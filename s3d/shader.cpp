/***************************************************************************
 *
 *  File:       shader.cpp
 *  Date:       20.07.2021
 *
 *  Github:     https://github.com/0xMartin
 *  Email:      martin.krcma1@gmail.com
 *
 *  Copyright (C) 2022 Martin Krcma
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 ***************************************************************************/

#include "shader.h"

#include "graphics3d.h"


ShaderProgram::ShaderProgram() {
    ShaderProgram::ID = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(ShaderProgram::ID);
}

GLuint ShaderProgram::getID() {
    return ShaderProgram::ID;
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

void ShaderProgram::setVec3(const std::string &name, GLfloat a1, GLfloat a2, GLfloat a3) {
    glUniform3f(glGetUniformLocation(
                           ShaderProgram::ID, name.c_str()), a1, a2, a3);
}

void ShaderProgram::setVec4(const std::string &name, GLfloat a1, GLfloat a2, GLfloat a3, GLfloat a4) {
    glUniform4f(glGetUniformLocation(
                           ShaderProgram::ID, name.c_str()), a1, a2, a3, a4);
}
