#ifndef SHADER_H
#define SHADER_H


#include "graphics.h"
#include <GLES3/gl3.h>
#include <vector>


class ShaderProgram
{
protected:
    std::vector<GLuint> shaders;
public:
    GLuint ID; /** program ID */

    ShaderProgram();

    /**
     * @brief use
     */
    void use();

    /**
     * @brief link
     */
    void link();

    /**
     * @brief addShader
     * @param source
     * @param type
     */
    void addShader(const GLchar * source, GLenum type);

    /**
     * @brief setBool
     * @param name
     * @param value
     */
    void setBool(const std::string &name, bool value);

    /**
     * @brief setInt
     * @param name
     * @param value
     */
    void setInt(const std::string &name, GLint value);

    /**
     * @brief setFloat
     * @param name
     * @param value
     */
    void setFloat(const std::string &name, GLfloat value);

    /**
     * @brief setMatrix4
     * @param name
     * @param value
     */
    void setMatrix4(const std::string &name, const GLfloat * value);
};

#endif // SHADER_H
