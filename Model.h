#pragma once
#include <GL/glew.h>

#include "AbstractObject.h"

class Model : public AbstractObject
{
public:
    Model(const float* vertices, size_t vertexCount);
    void draw() override;
    size_t getVertexCount() const;

    Model(GLuint vao, int indicesCount) : VAO(VAO), indicesCount(indicesCount) {}
    GLuint getVAO() const { return VAO; }
    int getIndicesCount() const { return indicesCount; }
    
protected:
    GLuint VAO;
    GLuint VBO;
    size_t vertexCount;
    int indicesCount;
};
