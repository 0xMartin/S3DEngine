/***************************************************************************
 *
 *  File:       default_shaders.h
 *  Date:       25.07.2021
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

#ifndef DEFAULT_SHADERS_H
#define DEFAULT_SHADERS_H



/*---------------------------Objects--------------------------------------------------------------*/
static const char * SHADER_OBJ_VERTEX = R"glsl(
    #version 330 core

    layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;
    layout(location = 2) in vec2 aUV;

    out vec2 UV;
    out vec3 Normal;
    out vec3 FragPos;

    uniform mat4 MVP;
    uniform mat4 M;

    void main(){
        gl_Position = MVP * vec4(aPosition, 1.0);
        UV = aUV;
        Normal = aNormal;
        FragPos = vec3(M * vec4(aPosition, 1.0));
    }
)glsl";

static const char * SHADER_OBJ_FRAGMENT = R"glsl(
    #version 330 core

    in vec2 UV;
    in vec3 Normal;
    in vec3 FragPos;

    out vec4 FragColor;

    //lights
    uniform vec3 lightPos;
    uniform vec3 lightColor;
    uniform vec3 viewPos;

    //object surface (texture or color)
    uniform vec4 Color;
    uniform sampler2D objTexture;

    void main(){
        vec4 objectColor = Color;
        objectColor += texture(objTexture, UV);
        if(objectColor.a < 0.1)
            discard;

        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = 0.5 * spec * lightColor;

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        vec3 ambient = 0.01 * lightColor;
        vec3 result = (ambient + diffuse + specular) * objectColor.rgb;
        FragColor = vec4(result, 1.0);
    }
)glsl";
/*------------------------------------------------------------------------------------------------*/



/*---------------------------SkyBox---------------------------------------------------------------*/
static const char * SHADER_SKY_VERTEX = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    out vec3 TexCoords;

    uniform mat4 MVP;

    void main()
    {
        TexCoords = aPos;
        gl_Position = MVP * vec4(aPos, 1.0);
    }
)glsl";

static const char * SHADER_SKY_FRAGMENT = R"glsl(
    #version 330 core
    out vec4 FragColor;

    in vec3 TexCoords;

    uniform samplerCube skybox;

    void main()
    {
        FragColor = texture(skybox, TexCoords);
    }
)glsl";
/*------------------------------------------------------------------------------------------------*/



/*---------------------------Image----------------------------------------------------------------*/
static const char * SHADER_IMG_VERTEX = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aUV;

    out vec2 UV;

    uniform mat4 MVP;

    void main()
    {
        UV = aUV;
        gl_Position = MVP * vec4(aPos, 1.0);
    }
)glsl";

static const char * SHADER_IMG_FRAGMENT = R"glsl(
    #version 330 core
    out vec4 FragColor;

    in vec2 UV;

    uniform sampler2D texture1;

    void main()
    {
        vec4 texColor = texture(texture1, UV);
        if(texColor.a < 0.1)
            discard;
        FragColor = texColor;
    }
)glsl";
/*------------------------------------------------------------------------------------------------*/


#endif // DEFAULT_SHADERS_H
