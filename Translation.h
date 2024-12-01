#pragma once
#include "AbstractTransform.h"

class Translation : public AbstractTransform
{
protected:
    mutable glm::vec3 offset;

public:
    Translation(const glm::vec3& offset = glm::vec3(0.0f));
    void setTranslation(const glm::vec3& offset);
    glm::mat4 getTransformMatrix() const override;
};
