#pragma once
#include <string>
#include <GL/glew.h>
#include "AbstractObject.h"

enum ModelType
{
    BASIC,
    TEXTURE
};

class ModelFactory
{
public:
    static AbstractObject* createModel(ModelType modelType, const float* model, size_t vertexCount);
    static AbstractObject* createModel(std::string fileName, GLuint mode);
private:
    static AbstractObject* createBasicModel(const float* model, size_t vertexCount);
    static AbstractObject* createTextureModel(const float* model, size_t vertexCount);
    static AbstractObject* createAssimpModel(std::string fileName, GLuint mode);
};
