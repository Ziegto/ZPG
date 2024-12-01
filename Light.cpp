#include "Light.h"
#include <iostream>

Light::Light(glm::vec3 position, glm::vec4 color, int type) : position(position), color(color), type(type)
{
}

void Light::attach(Observer* observer)
{
    observers.push_back(observer);
}

void Light::detach(Observer* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Light::notify()
{
    for (auto observer : observers)
    {
        if (id>=0)
            observer->update(this);
    }
}

void Light::update(Subject* subject)
{
    if (auto camera = dynamic_cast<Camera*>(subject)) {
        position = camera->getPosition();
        lightDirection = camera->getFront();
    }
    notify();
}


void Light::setPosition(glm::vec3 position)
{
    this->position = position;
    notify();
}

void Light::setColor(glm::vec4 color)
{
    this->color = color;
    notify();
}

void Light::setType(int type)
{
    this->type = type;
}

int Light::getType() const
{
    return type;
}

glm::vec3 Light::getPosition() const
{
    return position;
}

glm::vec4 Light::getColor() const
{
    return color;
}

glm::vec3 Light::getLightPosition()
{
    return lightDirection;
}

void Light::setId(int id)
{
    this->id = id;
}

int Light::getId()
{
    return id;
}

