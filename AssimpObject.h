#pragma once
#include <string>
#include <GL/glew.h>

#include "AbstractObject.h"

class AssimpObject : public AbstractObject
{
public:
    AssimpObject(std::string fileName, GLuint mode);
    void draw() override;
private:
    struct Vertex
    {
        float Position[3];
        float Normal[3];
        float Texture[2];
        float Tangent[3];
    };
    GLuint VAO = 0;
    int indicesCount = 0;
    GLuint mode;
    
};
