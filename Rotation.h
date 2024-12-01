#pragma once
#include "AbstractTransform.h"

class Rotation : public AbstractTransform
{
protected:
    mutable float angle;
    mutable glm::vec3 axis;

public:
    Rotation(float angle = 0.0f, const glm::vec3& axis = glm::vec3(0.0f, 1.0f, 0.0f));
    void setRotation(float degrees, const glm::vec3& axis);
    glm::mat4 getTransformMatrix() const override;
};
