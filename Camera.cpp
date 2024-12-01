#include "Camera.h"
#include "ShaderProgram.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up)
    : Position(position), WorldUp(up), Yaw(-90.0f), Pitch(0.0f), MovementSpeed(0.1f), MouseSensitivity(0.2f),
      projectionMat(glm::perspective(glm::radians(60.f), 4.f / 3.f, 0.1f, 100.f))
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getProjectionMatrix(float fov, float aspect, float near, float far)
{
    return glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projectionMat;
}

void Camera::moveForward()
{
    Position += Front * MovementSpeed;
    notify();
}

void Camera::moveBackward()
{
    Position -= Front * MovementSpeed;
    notify();
}

void Camera::moveLeft()
{
    Position -= Right * MovementSpeed;
    notify();
}

void Camera::moveRight()
{
    Position += Right * MovementSpeed;
    notify();
}

void Camera::updatePosition(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    updateCameraVectors();
    notify();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = normalize(front);
    Right = normalize(cross(Front, WorldUp));
    Up = normalize(cross(Right, Front));
}


void Camera::attach(Observer* observer)
{
    observers.push_back(observer);
}

void Camera::detach(Observer* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notify()
{
    for (auto observer : observers)
    {
        observer->update(this);
    }
}

void Camera::setRation(float fov, float aspect, float near, float far)
{
    this->aspect = aspect;
    projectionMat = glm::perspective(glm::radians(fov), aspect, near, far);
    notify();
}


void Camera::updateRation(float width, float height)
{
    aspect = width / height;
    setRation(60.f, aspect, 0.1f, 100.f);
}

glm::vec3 Camera::getPosition()
{
    return Position;
}

glm::vec3 Camera::getFront()
{
    return Front;
}