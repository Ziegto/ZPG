#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm/vec3.hpp"

class Material {
public:
    glm::vec3 ra;
    glm::vec3 rd;
    glm::vec3 rs;

    Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : ra(ambient), rd(diffuse), rs(specular) {}
};

#endif
