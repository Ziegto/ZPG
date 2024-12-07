#pragma once
#include "Model.h"

class SkyCube : public Model
{
public:
    SkyCube(const float* vertices, size_t vertexCount);
    void setSkyCubeBuffer(int buffer);
    void draw() override;
private:
    int buffer;
};
