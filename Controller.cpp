// Controller.cpp
#include "Controller.h"

#include "App.h"

Controller::Controller(GLFWwindow* window, Camera* camera, App* app)
    : window(window), camera(camera), app(app) {}

void Controller::processInput() {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveForward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveBackward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveRight();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !escKeyWasPressed) {
        isMouseCaptured = !isMouseCaptured;
        if (isMouseCaptured) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        escKeyWasPressed = true;
    } else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
        escKeyWasPressed = false;
    }
}

void Controller::mouseCallback(double xpos, double ypos) {
    if (!isMouseCaptured) return;

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float xoffset = xpos - (width / 2);
    float yoffset = (height / 2) - ypos;

    glfwSetCursorPos(window, width / 2, height / 2);
    camera->updatePosition(xoffset, yoffset);
}

void Controller::mouseButtonCallback(int button, int action, int mods) {
   if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        ypos = height - ypos;

        GLbyte color[4];
        GLfloat depth;
        GLuint stencil;

        glReadPixels(static_cast<GLint>(xpos), static_cast<GLint>(ypos), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(static_cast<GLint>(xpos), static_cast<GLint>(ypos), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(static_cast<GLint>(xpos), static_cast<GLint>(ypos), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &stencil);

        if (stencil != 0)
        {
            glm::vec3 screenPos(xpos, ypos, depth);
            glm::vec3 worldPos = glm::unProject(screenPos,
                                                camera->getViewMatrix(),
                                                camera->getProjectionMatrix(),
                                                glm::vec4(0, 0, width, height));
            app->addTreeAtPosition(worldPos);
        }
    }
}

void Controller::windowSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
    camera->updateRation(width, height);
}
