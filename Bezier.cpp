#include "Bezier.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Bezier::Bezier(float delta, float t, const glm::mat4& A, const glm::mat4& B)
    : delta(delta), t(t), A(A), B(B)
{
}

glm::mat4 Bezier::getTransformMatrix() const
{
   glm::mat4 M = glm::mat4(1.0f);
    if (t >= 1.0f || t <= 0.0f) delta *= -1;
    t += delta;
    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
    glm::vec3 p  = parameters * A * glm::transpose(B);
    M = glm::translate(M, p);

    return M;
}
