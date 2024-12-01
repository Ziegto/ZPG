#pragma once
#include "Subject.h"
#include "Observer.h"
#include <vector>
#include <glm/ext/vector_float3.hpp>
#include "Camera.h"
#include "Light.h"
#include "ShaderProgram.h"

class Subject;

class Light : public Subject, public Observer
{
public:
    Light(glm::vec3 position, glm::vec4 color, int type);
    void attach(Observer* observer) override;
    void detach(Observer* observer) override;
    void notify() override;
    void update(Subject* subject) override;
    void setPosition(glm::vec3 position);
    void setColor(glm::vec4 color);
    
    void setType(int type);
    int getType() const;

    glm::vec3 getPosition() const;
    glm::vec4 getColor() const;
    glm::vec3 getLightPosition();
    void setId(int id);
    int getId();

protected:
    std::vector<Observer*> observers;
    glm::vec3 position;
    glm::vec4 color;
    glm::vec3 lightDirection;
    int id = -1;
    int type;
};
