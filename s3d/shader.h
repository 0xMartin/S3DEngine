/***************************************************************************
 *
 *  File:       shader.h
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
