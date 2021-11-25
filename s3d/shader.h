#ifndef SHADER_H
#define SHADER_H


#include "api.h"
#include "graphics.h"
#include <GLES3/gl3.h>
#include <vector>


class S3D_EXPORT ShaderProgram
{
private:
    GLuint ID; /** program ID */

public:
    ShaderProgram();

    ~ShaderProgram();

    /**
     * @brief getID
     * @return
     */
    GLuint getID();

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

    /**
     * @brief setVec3
     * @param name
     * @param x
     * @param y
     * @param z
     */
    void setVec3(const std::string &name, GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief setVec4
     * @param name
     * @param a1
     * @param a2
     * @param a3
     * @param a4
     */
    void setVec4(const std::string &name, GLfloat a1, GLfloat a2, GLfloat a3, GLfloat a4);
};

#endif // SHADER_H
