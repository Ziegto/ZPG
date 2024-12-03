#include "App.h"
#include "./Models/tree.h"
#include "./Models/bushes.h"
#include "./Models/sphere.h"
#include "./Models/plain.h"
#include "./Models/triangle.h"
#include "./Models/skycube.h"
#include "./Models/suzi_smooth.h"
#include <cstdlib>
#include <iomanip>

#include "AssimpObject.h"
#include "SkyCube.h"
#include "DynamicRotation.h"
#include "DynamicTranslation.h"
#include "Material.h"
#include "ModelFactory.h"
#include "TextureObject.h"

#define GLM_ENABLE_EXPERIMENTAL


Camera* camera;
Material* matteMaterial;
Material* shinyMaterial;
Material* glowingMaterial;

App::App()
{
    camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1200, 1000, "ZPG", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    glewInit();
}

App::~App()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void App::window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera->updateRation(width, height);
}

void App::initialization()
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetWindowSizeCallback(window, window_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
    {
        auto app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if (app)
        {
            app->mouseButtonCallback(button, action, mods);
        }
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
    {
        auto app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if (app)
        {
            app->mouseCallback(xpos, ypos);
        }
    });

    glfwSetWindowUserPointer(window, this);
}

void App::createLights()
{
    light = new Light(glm::vec3(1.0f, 1.0f, 2.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 0);
    light2 = new Light(glm::vec3(0.f, 0.f, 0.f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), 0);
    light3 = new Light(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 0);
    light4 = new Light(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0);
    light5 = new Light(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0);
}


void App::createShaders()
{
    shaderLambert = new ShaderProgram("vertex_lambert.glsl", "fragment_lambert.glsl");
    shaderTriangle = new ShaderProgram("vertex_2d.glsl", "fragment_2d.glsl");
    shaderPhong = new ShaderProgram("vertex_phong.glsl", "fragment_phong.glsl");
    shaderBlinn = new ShaderProgram("vertex_blinn.glsl", "fragment_blinn.glsl");
    shaderConstant = new ShaderProgram("vertex_constant.glsl", "fragment_constant.glsl");
    shaderSkyCube = new ShaderProgram("PhongVertexShader.glsl", "PhongFragmentShader.glsl");

    matteMaterial = new Material(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.7f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f));
    shinyMaterial = new Material(glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
    glowingMaterial = new Material(glm::vec3(0.5f, 0.5f, 0.2f), glm::vec3(0.9f, 0.9f, 0.5f), glm::vec3(2.0f, 2.0f, 1.0f));

    light->attach(shaderLambert);
    light->attach(shaderConstant);
    light->attach(shaderPhong);
    light->attach(shaderBlinn);
    light->attach(shaderSkyCube);

    light2->attach(shaderLambert);
    light2->attach(shaderPhong);
    light2->attach(shaderBlinn);
    light2->attach(shaderConstant);
    light2->attach(shaderSkyCube);

    light3->attach(shaderLambert);
    light3->attach(shaderPhong);
    light3->attach(shaderBlinn);
    light3->attach(shaderConstant);
    light3->attach(shaderSkyCube);

    light4->attach(shaderLambert);
    light4->attach(shaderPhong);
    light4->attach(shaderBlinn);
    light4->attach(shaderConstant);
    light4->attach(shaderSkyCube);

    light5->attach(shaderLambert);
    light5->attach(shaderPhong);
    light5->attach(shaderBlinn);
    light5->attach(shaderConstant);
    light5->attach(shaderSkyCube);
}

Scene* App::createSceneWithModels(const std::vector<std::pair<DrawableObject*, ComposedTransform*>>& models, const std::vector<Light*>& lights)
{
    auto scene = new Scene(camera);

    for (const auto& modelData : models)
    {
        DrawableObject* object = modelData.first;
        camera->attach(object->getShader());
        scene->addObject(object, GL_TRIANGLES, 0, sizeof(tree) / (6 * sizeof(float)));
    }
    for (const auto& light : lights)
    {
        scene->addLight(light);
    }

    return scene;
}

void App::createModels()
{
    std::vector<Light*> scene1Lights = {light, light3, light4};
    std::vector<Light*> scene2Lights = {light, light5, light4};
    std::vector<Light*> scene4Lights = {light, light4};

    ModelFactory modelFactory;

    AbstractObject* treeModelInstance = dynamic_cast<Model*>(modelFactory.createModel(BASIC, tree, sizeof(tree) / sizeof(tree[0])));
    AbstractObject* bushModelInstance = dynamic_cast<Model*>(modelFactory.createModel(BASIC, bushes, sizeof(bushes) / sizeof(bushes[0])));
    AbstractObject* triangleModelInstace = dynamic_cast<Model*>(modelFactory.createModel(BASIC, triangle, sizeof(triangle) / sizeof(triangle[0])));
    AbstractObject* sphereModelInstance = dynamic_cast<Model*>(modelFactory.createModel(BASIC, sphere, sizeof(sphere) / sizeof(sphere[0])));
    AbstractObject* suziModelInstance = dynamic_cast<Model*>(modelFactory.createModel(BASIC, suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0])));
    AbstractObject* plainModelInstance = dynamic_cast<TextureObject*>(modelFactory.createModel(TEXTURE, plain, sizeof(plain) / sizeof(plain[0])));
    AbstractObject* assimpModelInstance = dynamic_cast<AssimpObject*>(modelFactory.createModel("./3DModels/house.obj", GL_TRIANGLES));
    AbstractObject* assimpModelLoginInstance = dynamic_cast<AssimpObject*>(modelFactory.createModel("./3DModels/login.obj", GL_TRIANGLES));
    
    // AbstractObject* treeModelInstance = (ModelFactory::createModel(BASIC, tree, sizeof(tree) / sizeof(tree[0])));
    // AbstractObject* bushModelInstance = (ModelFactory::createModel(BASIC, bushes, sizeof(bushes) / sizeof(bushes[0])));
    // AbstractObject* triangleModelInstace = (ModelFactory::createModel(BASIC, triangle, sizeof(triangle) / sizeof(triangle[0])));
    // AbstractObject* sphereModelInstance = (ModelFactory::createModel(BASIC, sphere, sizeof(sphere) / sizeof(sphere[0])));
    // AbstractObject* suziModelInstance = (ModelFactory::createModel(BASIC, suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0])));
    // AbstractObject* plainModelInstance = (ModelFactory::createModel(TEXTURE, plain, sizeof(plain) / sizeof(plain[0])));
    // AbstractObject* assimpModelInstance = (ModelFactory::createModel("./3DModels/house.obj", GL_TRIANGLES));
    // AbstractObject* assimpModelLoginInstance = (ModelFactory::createModel("./3DModels/login.obj", GL_TRIANGLES));
    
    //les
    auto drawablePlain = new DrawableObject(plainModelInstance, shaderLambert);
    drawablePlain->setTexture(0, "./Structures/grass.png");
    drawablePlain->setMaterial(glowingMaterial);
    auto plainTransform = new ComposedTransform();
    plainTransform->addTransform(new Translation(glm::vec3(0.f, -1.0f, 0.f)));
    plainTransform->addTransform(new Scale(glm::vec3(30.f, 30.f, 30.f)));
    drawablePlain->setTransformation(plainTransform);
    scene1Models.push_back(std::make_pair(drawablePlain, plainTransform));

    auto drawableHouse = new DrawableObject(assimpModelInstance, shaderLambert);
    drawableHouse->setTexture(1, "./Structures/house.png");
    drawableHouse->setMaterial(glowingMaterial);
    auto houseTransform = new ComposedTransform();
    houseTransform->addTransform(new Translation(glm::vec3(0.f, -1.0f, 0.f)));
    houseTransform->addTransform(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    drawableHouse->setTransformation(houseTransform);
    scene1Models.push_back(std::make_pair(drawableHouse, houseTransform));

    auto drawableLogin = new DrawableObject(assimpModelLoginInstance, shaderLambert);
    drawableLogin->setTexture(2, "./Structures/wooden_fence.png");
    drawableLogin->setMaterial(glowingMaterial);
    auto loginTransform = new ComposedTransform();
    loginTransform->addTransform(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    loginTransform->addTransform(new Translation(glm::vec3(10.f, 0.f, 0.f)));
    drawableLogin->setTransformation(loginTransform);
    scene1Models.push_back(std::make_pair(drawableLogin, loginTransform));

    // auto drawableAxe = new DrawableObject(assimpModelAxeInstance, shaderLambert);
    // drawableAxe->setTexture(textureID4, 2);
    // drawableAxe->setMaterial(glowingMaterial);
    // auto axeTransform = new ComposedTransform();
    // axeTransform->addTransform(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    // axeTransform->addTransform(new Translation(glm::vec3(4.f, 0.f, 0.f)));
    // drawableAxe->setTransformation(axeTransform);
    // scene1Models.push_back(std::make_pair(drawableAxe, axeTransform));
    
    for (int i = 0; i < 50; i++)
    {
        auto drawableTree = new DrawableObject(treeModelInstance, shaderPhong);
        drawableTree->setMaterial(glowingMaterial);
    
        auto treeTransform = new ComposedTransform();
    
        float treeX = static_cast<float>(rand()) / (RAND_MAX / 60.0f) - 30.0f;
        float treeZ = static_cast<float>(rand()) / (RAND_MAX / 60.0f) - 30.0f;
        float treeScale = 0.1f + static_cast<float>(rand()) / (RAND_MAX / (0.5f - 0.1f));
    
        treeTransform->addTransform(new Translation(glm::vec3(treeX, -1.0f, treeZ)));
        treeTransform->addTransform(new Scale(glm::vec3(treeScale, treeScale, treeScale)));
        drawableTree->setTransformation(treeTransform);
        scene1Models.push_back(std::make_pair(drawableTree, treeTransform));
    }
    
    for (int i = 0; i < 15; i++)
    {
        auto drawableHmyz = new DrawableObject(sphereModelInstance, shaderPhong);
        drawableHmyz->setMaterial(glowingMaterial);
        auto hmyzTransform = new ComposedTransform();
        float treeX = static_cast<float>(rand()) / (RAND_MAX / 60.0f) - 30.0f;
        float treeZ = static_cast<float>(rand()) / (RAND_MAX / 60.0f) - 30.0f;
        hmyzTransform->addTransform(new Translation(glm::vec3(treeX, 0.f, treeZ)));
        hmyzTransform->addTransform(new Scale(glm::vec3(0.2f, 0.2f, 0.2f)));
        hmyzTransform->addTransform(new DynamicTranslation(-10.f, 10.f, -10.f, 10.f, -10.f, 10.f, 5.f));
        drawableHmyz->setTransformation(hmyzTransform);
    
        scene1Models.push_back(std::make_pair(drawableHmyz, hmyzTransform));
    }
    
    for (int i = 0; i < 30; i++)
    {
        auto drawableBush = new DrawableObject(bushModelInstance, shaderPhong);
        drawableBush->setMaterial(glowingMaterial);
        auto bushTransform = new ComposedTransform();
    
        float bushX = static_cast<float>(rand()) / (RAND_MAX / 60.0f) - 30.0f;
        float bushZ = static_cast<float>(rand()) / (RAND_MAX / 60.0f) - 30.0f;
        float bushScale = 0.1f + static_cast<float>(rand()) / (RAND_MAX / (0.5f - 0.1f));
    
        bushTransform->addTransform(new Translation(glm::vec3(bushX, -1.0f, bushZ)));
        bushTransform->addTransform(new Scale(glm::vec3(2.f, 2.f, 2.f)));
    
        drawableBush->setTransformation(bushTransform);
        scene1Models.push_back(std::make_pair(drawableBush, bushTransform));
    }
    Scene* scene1 = createSceneWithModels(scene1Models, scene1Lights);
    scenes.push_back(scene1);
    
    
    //4 koule
    for (int i = 0; i < 4; i++)
    {
        auto drawableSphere = new DrawableObject(sphereModelInstance, shaderPhong);
        drawableSphere->setMaterial(glowingMaterial);
        auto sphereTransform = new ComposedTransform();
        sphereTransform->addTransform(new Translation(glm::vec3((i % 2) * 3 - 1.5f, (i / 2) * 3 - 1.5f, 0.5f)));
        drawableSphere->setTransformation(sphereTransform);
        scene2Models.push_back(std::make_pair(drawableSphere, sphereTransform));
    }
    Scene* scene2 = createSceneWithModels(scene2Models, scene2Lights);
    scenes.push_back(scene2);


    //trojuhelnik
    auto drawableTriangle = new DrawableObject(triangleModelInstace, shaderTriangle);
    auto scene3 = new Scene(camera);
    scene3->addObject(drawableTriangle, GL_TRIANGLES, 0, sizeof(triangle) / (3 * sizeof(float)));
    scenes.push_back(scene3);

    //4 objekty vedle sebe
    //..1
    auto drawableObject1 = new DrawableObject(sphereModelInstance, shaderPhong);
    drawableObject1->setMaterial(shinyMaterial);
    auto transform1 = new ComposedTransform();
    //transform1->addTransform(new Translation(glm::vec3(0.f, 0.f, 0.f)));
    transform1->addTransform(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    transform1->addTransform(new DynamicRotation(45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
    drawableObject1->setTransformation(transform1);
    scene4Models.push_back(std::make_pair(drawableObject1, transform1));
    //..2
    auto drawableObject2 = new DrawableObject(suziModelInstance, shaderBlinn);
    drawableObject2->setMaterial(matteMaterial);
    auto transform2 = new ComposedTransform();
    transform2->addTransform(new Translation(glm::vec3(3.f, 0.0f, 0.f)));
    transform2->addTransform(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    transform2->addTransform(new DynamicRotation(45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
    drawableObject2->setTransformation(transform2);
    scene4Models.push_back(std::make_pair(drawableObject2, transform2));
    //..3
    // auto drawableObject3 = new DrawableObject(plainModelInstance, shaderLambert);
    // drawableObject3->setTexture(4, "./Structures/wooden_fence.png");
    // drawableObject3->setMaterial(glowingMaterial);
    // auto transform3 = new ComposedTransform();
    // transform3->addTransform(new Translation(glm::vec3(6.f, -0.5f, 0.f)));
    // transform3->addTransform(new Scale(glm::vec3(1.5f, 1.5f, 1.5f)));
    // transform3->addTransform(new DynamicRotation(45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
    // drawableObject3->setTransformation(transform3);
    // scene4Models.push_back(std::make_pair(drawableObject3, transform3));
    //..4
    auto drawableObject4 = new DrawableObject(treeModelInstance, shaderConstant);
    drawableObject4->setMaterial(glowingMaterial);
    auto transform4 = new ComposedTransform();
    transform4->addTransform(new Translation(glm::vec3(9.f, -0.5f, 0.f)));
    transform4->addTransform(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    transform4->addTransform(new DynamicRotation(45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
    drawableObject4->setTransformation(transform4);
    scene4Models.push_back(std::make_pair(drawableObject4, transform4));
    Scene* scene4 = createSceneWithModels(scene4Models, scene4Lights);
    scenes.push_back(scene4);
    
    currentScene = scenes[2];
}

void App::switchScene(int sceneIndex)
{
    if (sceneIndex >= 0 && sceneIndex < scenes.size())
    {
        currentScene = scenes[sceneIndex];
    }
    scenes[sceneIndex]->initLight();
    if (sceneIndex == 0)
    {
        scenes[sceneIndex]->setSkyEnabled(true);
    }
}

void App::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveForward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveBackward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveRight();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        isMouseCaptured = !isMouseCaptured;

        if (isMouseCaptured)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(window, 1200 / 2, 1000 / 2);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}


void App::mouseCallback(double xpos, double ypos)
{
    if (!isMouseCaptured)
    {
        return;
    }

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float xoffset = xpos - (width / 2);
    float yoffset = (height / 2) - ypos;

    glfwSetCursorPos(window, width / 2, height / 2);

    camera->updatePosition(xoffset, yoffset);
}

void App::mouseButtonCallback(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}


void App::run()
{
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        currentScene->draw();
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            camera->attach(light4);
            switchScene(0);
        }
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            camera->attach(light5);
            switchScene(1);
        }
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        {
            camera->attach(light4);
            switchScene(2);
        }
        else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        {
            camera->attach(light4);
            switchScene(3);
        }

        glfwSwapBuffers(window);
    }
}