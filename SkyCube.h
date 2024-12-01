#pragma once
#include "Model.h"

class SkyCube : public Model
{
public:
    SkyCube(const float* vertices, size_t vertexCount);
    void draw() override;
private:
};
