#pragma once
#include <vector>
#include "AbstractTransform.h"

class ComposedTransform : public AbstractTransform
{
    std::vector<AbstractTransform*> transforms;

public:
    ~ComposedTransform() override;
    void addTransform(AbstractTransform* transform);
    glm::mat4 getTransformMatrix() const override;

    const std::vector<AbstractTransform*>& getTransforms() const;
};
