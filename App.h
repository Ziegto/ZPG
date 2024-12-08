#ifndef APP_H
#define APP_H
#pragma once
#include "Camera.h"
#include "ShaderProgram.h"
#include "Model.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "DrawableObject.h"
#include "Scene.h"
#include "ShaderLoader.h"
#include "Light.h"
#include "ComposedTransform.h"
#include "Rotation.h"
#include "Translation.h"
#include "Scale.h"
#include <vector>
#include <SOIL.h>


class App
{
public:
    App();
    ~App();

    void initialization();
    void createShaders();
    void createModels();
    void run();
    void switchScene(int sceneIndex);
    Scene* createSceneWithModels(const std::vector<std::pair<DrawableObject*, ComposedTransform*>>& models,
                                 const std::vector<Light*>& lights);
    void createLights();
    void addTreeAtPosition(const glm::vec3& position);
    void attachLightsToShaders();    
private:
    bool isMouseCaptured = true;
    GLFWwindow* window;

    Scene* currentScene;

    std::vector<Scene*> scenes;
    std::vector<Shader*> shaders;

    GLint shape_location;

    ShaderLoader* shaderLoader;

    ShaderProgram* shaderLambert;
    ShaderProgram* shaderTriangle;
    ShaderProgram* shaderConstant;
    ShaderProgram* shaderPhong;
    ShaderProgram* shaderBlinn;
    ShaderProgram* shaderSkyCube;
    ShaderProgram* shaderHouse;
    ShaderProgram* shaderPhongNight;
    
    Light* light;
    Light* light2;
    Light* light3;
    Light* light4;
    Light* light5;
    Light* flashlight;

    std::vector<std::pair<DrawableObject*, ComposedTransform*>> scene1Models;
    std::vector<std::pair<DrawableObject*, ComposedTransform*>> scene2Models;
    std::vector<std::pair<DrawableObject*, ComposedTransform*>> scene3Models;
    std::vector<std::pair<DrawableObject*, ComposedTransform*>> scene4Models;
    std::vector<std::pair<DrawableObject*, ComposedTransform*>> scene5Models;
};

#endif