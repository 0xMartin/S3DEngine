/******************************************************************************
 * S3D Engine
 *
 * @file       model.cpp
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#include "model.h"

#include <iostream>
#include <string>
#include <string.h>
#include "io.h"

Model::Model(const char * path) {
    Model::offset = (Vertex3){0.0, 0.0, 0.0};
    Model::rotation = (Vertex3){0.0, 0.0, 0.0};
    Model::buffer = new VertexDataBuffer(VBO_Color);
    Model::texture = NULL;
    Model::loadModel(path);

    Model::setOffset((Vertex3){0.0, 0.0, 0.0});
    Model::setScale((Vertex3){1.0, 1.0, 1.0});
    Model::setRotation((Vertex3){0.0, 0.0, 0.0});
}

Model::~Model() {
    if(Model::buffer) delete Model::buffer;
}

bool Model::loadModel(const char * path) {
    if(path == NULL) {
        std::cerr << __FUNCTION__ << ": path is NULL" << std::endl;
        return false;
    }

    /**
     * read .obj file
     */
    std::vector<std::string> lines;
    if(!IO_readStringFromFile(path, lines)) {
        std::cerr << __FUNCTION__ << ": impossible to open the file [" << path << "]" << std::endl;
        return false;
    }

    std::vector<Vertex3> vertices;
    std::vector<Point> texture_coordinates;
    std::vector<Vertex3> normals;
    std::vector<Triangle3> triangles;

    /**
     * first load all vertices, texture coordinates and normals
     */
    const char * c_data;
    for(std::string & line : lines) {
        c_data = line.c_str();

        char lineHeader[128];
        sscanf(c_data, "%s", lineHeader);

        /**
         *  geometric vertices
         */
        if (strcmp(lineHeader, "v") == 0 ){
            Vertex3 vertex;
            sscanf(c_data, "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            vertices.push_back(vertex);

            /**
             *  texture coordinates
             */
        } else if (strcmp(lineHeader, "vt") == 0 ) {
            Point vt;
            sscanf(c_data, "vt %f %f\n", &vt.x, &vt.y );
            texture_coordinates.push_back(vt);

            /**
             *  vertex normals
             */
        } else if (strcmp(lineHeader, "vn") == 0 ) {
            Vertex3 vn;
            sscanf(c_data, "vn %f %f %f\n", &vn.x, &vn.y, &vn.z );
            normals.push_back(vn);
        }
    }


    /**
     *  build model faces from (v, vt, vn)
     */

    Triangle3 triangle;
    int matches;
    unsigned int vertexIndex[3], vtIndex[3], normalIndex[3];

    for(std::string & line : lines) {
        c_data = line.c_str();

        char lineHeader[128];
        sscanf(c_data, "%s", lineHeader);
        if (strcmp(lineHeader, "f") == 0 ) {

            //format: v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
            matches = sscanf(c_data, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &vtIndex[0], &normalIndex[0],
                    &vertexIndex[1], &vtIndex[1], &normalIndex[1],
                    &vertexIndex[2], &vtIndex[2], &normalIndex[2]);
            if(matches == 9) {
                //add new triangle
                triangle.v[0] = &vertices[vertexIndex[0] - 1];
                triangle.v[1] = &vertices[vertexIndex[1] - 1];
                triangle.v[2] = &vertices[vertexIndex[2] - 1];

                triangle.vt[0] = &texture_coordinates[vtIndex[0] - 1];
                triangle.vt[1] = &texture_coordinates[vtIndex[1] - 1];
                triangle.vt[2] = &texture_coordinates[vtIndex[2] - 1];

                triangle.vn[0] = &normals[normalIndex[0] - 1];
                triangle.vn[1] = &normals[normalIndex[1] - 1];
                triangle.vn[2] = &normals[normalIndex[2] - 1];

                triangles.push_back(triangle);
            } else {

                //format: v1//vn1 v2//vn2 v3//vn3
                matches = sscanf(c_data, "f %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0],
                        &vertexIndex[1], &normalIndex[1],
                        &vertexIndex[2], &normalIndex[2]);
                if(matches == 6) {
                    //add new triangle
                    triangle.v[0] = &vertices[vertexIndex[0] - 1];
                    triangle.v[1] = &vertices[vertexIndex[1] - 1];
                    triangle.v[2] = &vertices[vertexIndex[2] - 1];

                    triangle.vt[0] = 0;
                    triangle.vt[1] = 0;
                    triangle.vt[2] = 0;

                    triangle.vn[0] = &normals[normalIndex[0] - 1];
                    triangle.vn[1] = &normals[normalIndex[1] - 1];
                    triangle.vn[2] = &normals[normalIndex[2] - 1];

                    triangles.push_back(triangle);
                } else {

                    //format: v1/vt1 v2/vt2 v3/vt3
                    matches = sscanf(c_data, "f %d/%d %d/%d %d/%d\n",
                                     &vertexIndex[0], &vtIndex[0],
                            &vertexIndex[1], &vtIndex[1],
                            &vertexIndex[2], &vtIndex[2]);
                    if(matches == 6) {
                        //add new triangle
                        triangle.v[0] = &vertices[vertexIndex[0] - 1];
                        triangle.v[1] = &vertices[vertexIndex[1] - 1];
                        triangle.v[2] = &vertices[vertexIndex[2] - 1];

                        triangle.vt[0] = &texture_coordinates[vtIndex[0] - 1];
                        triangle.vt[1] = &texture_coordinates[vtIndex[1] - 1];
                        triangle.vt[2] = &texture_coordinates[vtIndex[2] - 1];

                        triangle.vn[0] = 0;
                        triangle.vn[1] = 0;
                        triangle.vn[2] = 0;

                        triangles.push_back(triangle);
                    } else {

                        //format: v1 v2 v3
                        matches = sscanf(c_data, "f %d %d %d\n",
                                         &vertexIndex[0],
                                &vertexIndex[1],
                                &vertexIndex[2]);
                        if(matches == 3) {
                            //add new triangle
                            triangle.v[0] = &vertices[vertexIndex[0] - 1];
                            triangle.v[1] = &vertices[vertexIndex[1] - 1];
                            triangle.v[2] = &vertices[vertexIndex[2] - 1];

                            triangle.vt[0] = 0;
                            triangle.vt[1] = 0;
                            triangle.vt[2] = 0;

                            triangle.vn[0] = 0;
                            triangle.vn[1] = 0;
                            triangle.vn[2] = 0;

                            triangles.push_back(triangle);
                        } else {
                            std::cerr << __FUNCTION__ << ": file can't be read [" << path << "]" << std::endl;
                            return false;
                        }
                    }
                }
            }
        }
    }

    //convert model to float buffer
    if(Model::buffer == NULL) return false;
    if(Model::buffer->buildVertexData(triangles, Model::buffer->type)) return false;

    return true;
}

void Model::setTexture(Texture * texture) {
    if(texture == NULL) return;
    Model::texture = texture;
    Model::buffer->type = (Model::texture == NULL) ? VBO_Color : VBO_Texture;
}

void Model::render(Graphics * graphics) {
    Graphics3D * g3 = (Graphics3D *) graphics;

    glPushMatrix();

    //model offset
    glTranslatef(Model::offset.x, Model::offset.y,
                 Model::offset.z);

    //rotate model
    glRotatef(Model::rotation.x, 1.0, 0.0, 0.0);
    glRotatef(Model::rotation.y, 0.0, 1.0, 0.0);
    glRotatef(Model::rotation.z, 0.0, 0.0, 1.0);

    glScalef(Model::scale.x, Model::scale.y, Model::scale.z);

    //bind texture if exists
    if(texture != NULL) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->textureID);
        g3->setColorRGB(1.0, 1.0, 1.0, 1.0);
    }

    //draw model
    g3->drawVertexDataBuffer(Model::buffer, glm::value_ptr(Model::modelTransformationMatrix));

    //unbind texture
    if(texture != NULL) {
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glPopMatrix();
}

void Model::setOffset(Vertex3 pos) {
    Model::offset = pos;
    Model::translateMatrix = glm::translate(glm::mat4(1.0), glm::vec3(pos.x, pos.y, pos.z));
    Model::computeTransformationModelMatrix();
}

void Model::setRotation(Vertex3 rotation) {
    Model::rotation = rotation;
    Model::rotateMatrix = glm::rotate(glm::mat4(1.0), rotation.x, glm::vec3(1.0, 0.0, 0.0));
    Model::rotateMatrix = glm::rotate(Model::rotateMatrix, rotation.y, glm::vec3(0.0, 1.0, 0.0));
    Model::rotateMatrix = glm::rotate(Model::rotateMatrix, rotation.z, glm::vec3(0.0, 0.0, 1.0));
    Model::computeTransformationModelMatrix();
}

void Model::setScale(Vertex3 scale) {
    Model::scale = scale;
    Model::scaleMatrix = glm::scale(glm::mat4(1.0), glm::vec3(scale.x, scale.y, scale.z));
    Model::computeTransformationModelMatrix();
}

GLfloat * Model::getModelTranformationMatrix() {
    return glm::value_ptr(Model::modelTransformationMatrix);
}
#include <glm/gtx/string_cast.hpp>
void Model::computeTransformationModelMatrix() {
    Model::modelTransformationMatrix = Model::translateMatrix * Model::rotateMatrix * Model::scaleMatrix;
    //std::cout<<glm::to_string(Model::translateMatrix)<<std::endl;
}
