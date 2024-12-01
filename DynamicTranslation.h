#pragma once
#include "Translation.h"
#include <random>

class DynamicTranslation : public Translation
{
    mutable std::default_random_engine generator;
    mutable std::uniform_real_distribution<float> distributionX;
    mutable std::uniform_real_distribution<float> distributionY;
    mutable std::uniform_real_distribution<float> distributionZ;

    mutable float lastUpdateTime = 0.0f;
    float interval;

    mutable glm::vec3 offset;
    mutable glm::vec3 targetOffset;

public:
    DynamicTranslation(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float interval);
    glm::mat4 getTransformMatrix() const override;
};
