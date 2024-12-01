#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class AbstractTransform
{
public:
    virtual ~AbstractTransform()
    {
    }

    virtual glm::mat4 getTransformMatrix() const = 0;
};
