#include "Scale.h"


Scale::Scale(const glm::vec3& factor)
{
    this->factor = factor;
}

void Scale::setScale(const glm::vec3& factor)
{
    this->factor = factor;
}

glm::mat4 Scale::getTransformMatrix() const
{
    return scale(glm::mat4(1.0f), this->factor);
}
