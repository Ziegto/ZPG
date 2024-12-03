#include "ModelFactory.h"
#include "Model.h"
#include "TextureObject.h"
#include "AssimpObject.h"

AbstractObject* ModelFactory::createModel(ModelType modelType, const float* model, size_t vertexCount)
{
    switch (modelType)
    {
    case BASIC:
        return createBasicModel(model, vertexCount);
    case TEXTURE:
        return createTextureModel(model, vertexCount);
    default:
        return nullptr;
    }
}

AbstractObject* ModelFactory::createModel(std::string fileName, GLuint mode)
{
    return createAssimpModel(fileName, mode);
}

AbstractObject* ModelFactory::createBasicModel(const float* model, size_t vertexCount)
{
    return new Model(model, vertexCount);
}

AbstractObject* ModelFactory::createTextureModel(const float* model, size_t vertexCount)
{
    return new TextureObject(model, vertexCount);
}

AbstractObject* ModelFactory::createAssimpModel(std::string fileName, GLuint mode)
{
    return new AssimpObject(fileName, mode);
}
