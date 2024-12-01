#include "Rotation.h"


Rotation::Rotation(float angle, const glm::vec3& axis)
{
    this->angle = angle;
    this->axis = axis;
}

void Rotation::setRotation(float degrees, const glm::vec3& axis)
{
    this->angle = degrees;
    this->axis = axis;
}

glm::mat4 Rotation::getTransformMatrix() const
{
    return rotate(glm::mat4(1.0f), glm::radians(this->angle), this->axis);
}
