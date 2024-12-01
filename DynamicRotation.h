#pragma once
#include "Rotation.h"

class DynamicRotation : public Rotation
{
    float rotationSpeed;
    mutable float lastUpdateTime = 0.0f;

public:
    DynamicRotation(float rotationSpeed, const glm::vec3& axis);
    glm::mat4 getTransformMatrix() const override;
};
