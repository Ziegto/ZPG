#include "ComposedTransform.h"

ComposedTransform::~ComposedTransform()
{
    for (AbstractTransform* transform : this->transforms)
    {
        delete transform;
    }
}

void ComposedTransform::addTransform(AbstractTransform* transform)
{
    this->transforms.push_back(transform);
}

glm::mat4 ComposedTransform::getTransformMatrix() const
{
    glm::mat4 result(1.0f);
    for (const AbstractTransform* transform : this->transforms)
    {
        result *= transform->getTransformMatrix();
    }
    return result;
}

const std::vector<AbstractTransform*>& ComposedTransform::getTransforms() const
{
    return transforms;
}
