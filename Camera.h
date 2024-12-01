#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Observer.h"
#include "Subject.h"

class Shader;

class Camera : public Subject
{
public:
    Camera(glm::vec3 position, glm::vec3 up);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(float fov, float aspect, float near, float far);
    glm::mat4 getProjectionMatrix();

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

    void updatePosition(float xoffset, float yoffset);

    void attach(Observer* observer) override;
    void detach(Observer* observer) override;
    void notify() override;

    glm::vec3 getPosition();

    glm::vec3 getFront();

    void setRation(float fov, float aspect, float near, float far);
    void updateRation(float width, float height);

private:
    std::vector<Observer*> observers;
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;

    void updateCameraVectors();

    float aspect;
    glm::mat4 projectionMat;
};

#endif
