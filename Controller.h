// Controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "App.h"
#include "Controller.h"

class App;

class Controller {
public:
    explicit Controller(GLFWwindow* window, Camera* camera, App* app);
    void processInput();
    void mouseCallback(double xpos, double ypos);
    void mouseButtonCallback(int button, int action, int mods);
    void windowSizeCallback(int width, int height);
private:
    GLFWwindow* window;
    Camera* camera;
    App* app;
    bool isMouseCaptured = true;
    bool escKeyWasPressed = false;
};

#endif // CONTROLLER_H
