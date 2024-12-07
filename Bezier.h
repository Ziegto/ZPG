#pragma once
#include "Translation.h"

class Bezier : public Translation
{
public:
    Bezier(float delta, float t, const glm::mat4& A, const glm::mat4& B);
    glm::mat4 getTransformMatrix() const override;

private:
    glm::mat4 A;
    glm::mat4 B;
    mutable float delta;
    mutable float t;
};
