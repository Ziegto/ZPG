#include "DynamicTranslation.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

DynamicTranslation::DynamicTranslation(float minX, float maxX, float minY, float maxY, float minZ, float maxZ,
                                       float interval)
    : Translation(glm::vec3(0.0f)),
      distributionX(minX, maxX),
      distributionY(glm::max(0.0f, minY), maxY),
      distributionZ(minZ, maxZ),
      interval(interval),
      offset(glm::vec3(0.0f)),
      targetOffset(glm::vec3(0.0f)),
      lastUpdateTime(static_cast<float>(glfwGetTime()))
{
    generator.seed(static_cast<unsigned int>(glfwGetTime() * 1000) + reinterpret_cast<std::uintptr_t>(this));

    targetOffset = glm::vec3(
        distributionX(generator),
        distributionY(generator),
        distributionZ(generator)
    );
}

glm::mat4 DynamicTranslation::getTransformMatrix() const
{
    float currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = currentTime - this->lastUpdateTime;

    if (deltaTime >= interval) 
    {
        offset = targetOffset;
        targetOffset = glm::vec3(
            distributionX(generator),
            distributionY(generator),
            distributionZ(generator)
        );
        lastUpdateTime = currentTime;
        deltaTime = 0.0f;
    }

    float alpha = glm::clamp(deltaTime / interval, 0.0f, 1.0f);
    glm::vec3 interpolatedPosition = glm::mix(offset, targetOffset, alpha);

    return glm::translate(glm::mat4(1.0f), interpolatedPosition);
}
