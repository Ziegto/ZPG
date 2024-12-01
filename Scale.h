#pragma once
#include "AbstractTransform.h"


class Scale : public AbstractTransform
{
    glm::vec3 factor;

public:
    Scale(const glm::vec3& factor = glm::vec3(1.0f));
    void setScale(const glm::vec3& factor);
    glm::mat4 getTransformMatrix() const override;
};
