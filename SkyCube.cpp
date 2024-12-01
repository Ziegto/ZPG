#include "SkyCube.h"

#include <cstddef>
#include <iostream>
#include <SOIL.h>

SkyCube::SkyCube(const float* vertices, size_t vertexCount): Model(vertices, vertexCount) 
{
    this->vertexCount = vertexCount;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

    glActiveTexture(GL_TEXTURE0);
    
    GLuint image = SOIL_load_OGL_cubemap("./Structures/posx.jpg", "./Structures/negx.jpg", "./Structures/posy.jpg", "./Structures/negy.jpg", "./Structures/posz.jpg", "./Structures/negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (image == NULL) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, image);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void SkyCube::draw()
{
    glDepthMask(GL_FALSE);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0,vertexCount);
    glDepthMask(GL_TRUE);
}