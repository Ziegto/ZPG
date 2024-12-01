#pragma once
#include "Model.h"

class TextureObject : public Model
{
public:
    TextureObject(const float* vertices, size_t vertexCount);
    void draw() override;
private:
};
