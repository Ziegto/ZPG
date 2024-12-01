#include "DynamicRotation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

DynamicRotation::DynamicRotation(float rotationSpeed, const glm::vec3& axis)
    : Rotation(0.0f, axis), rotationSpeed(rotationSpeed)
{
}

glm::mat4 DynamicRotation::getTransformMatrix() const
{
    float currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = currentTime - this->lastUpdateTime;
    this->lastUpdateTime = currentTime;

    this->angle += rotationSpeed * deltaTime;

    if (this->angle >= 360.0f)
    {
        this->angle -= 360.0f;
    }

    return rotate(glm::mat4(1.0f), glm::radians(this->angle), this->axis);
}
