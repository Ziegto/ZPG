#include "Scene.h"
#include <glm/gtc/type_ptr.hpp>

#include "SkyCube.h"
#include "Translation.h"
#include "Models/skycube.h"


Scene::Scene(Camera* cam) : camera(cam)
{
}

Scene::~Scene()
{
    for (auto& object : objects)
    {
        delete object;
    }
}

void Scene::addObject(DrawableObject* object, GLenum mode, int start, int count)
{
    objects.push_back(object);
    modes.push_back(mode);
    starts.push_back(start);
    counts.push_back(count);
    shaders.push_back(object->getShader());
}


std::vector<ComposedTransform*> Scene::getTransforms() const
{
    std::vector<ComposedTransform*> transforms;
    for (auto& object : objects)
    {
        transforms.push_back(object->getTransformation());
    }
    return transforms;
}

void Scene::initLight()
{
    if (!lightsInitializedFlag)
    {
        for (int i = 0; i < lights.size(); i++)
        {
            lights[i]->setId(i);
            lights[i]->notify();
        }
        lightsInitializedFlag = true;
    }
}

void Scene::addLight(Light* light)
{
    lights.push_back(light);
}

void Scene::setSkyEnabled(bool enabled)
{
    skyCube = new SkyCube(skycube, 108);
    shaderSkyCube = new ShaderProgram("PhongVertexShader.glsl", "PhongFragmentShader.glsl");
    skyCubeDrawable = new DrawableObject(skyCube, shaderSkyCube);
    shaders.push_back(shaderSkyCube);
    camera->attach(shaderSkyCube);
    sky = enabled;
}

void Scene::setFreezeSkyCube()
{
    if (freezeSkyCube == 0)
    {
        freezeSkyCube = 1;
        skyCube->setSkyCubeBuffer(0);
    }
    else if (freezeSkyCube == 1)
    {
        freezeSkyCube = 0;
        skyCube->setSkyCubeBuffer(1);
    }
}

bool Scene::lightsInitialized() const
{
    return lightsInitializedFlag;
}

void Scene::clearLights()
{
    lightsInitializedFlag = false;
}

void Scene::draw()
{
    if (sky)
    {
        ShaderProgram* currentShader = skyCubeDrawable->getShader();
        skyCubeDrawable->draw(GL_TRIANGLES, 0, 36);
        auto transform = new ComposedTransform();
        transform->addTransform(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
        skyCubeDrawable->setTransformation(transform);
        glm::mat4 modelMatrix = skyCubeDrawable->getModelMatrix();
        currentShader->setUniformSkyCube("freeze", freezeSkyCube);
        currentShader->setUniform("modelMatrix", modelMatrix);
    }

    for (size_t i = 0; i < objects.size(); ++i)
    {
        DrawableObject* object = objects[i];
        ShaderProgram* currentShader = object->getShader();
        Material* material = object->getMaterial();

        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, static_cast<GLuint>(i + 1), 0xFF);

        currentShader->setNumberLights(lights.size());
        currentShader->use();

        glm::mat4 modelMatrix = object->getModelMatrix();
        currentShader->setUniform("modelMatrix", modelMatrix);

        if (material)
        {
            currentShader->setUniform3("material.ra", material->ra);
            currentShader->setUniform3("material.rd", material->rd);
            currentShader->setUniform3("material.rs", material->rs);
        }

        GLuint textureUnit = object->getTextureUnit();
        GLuint textureID = object->getTextureID();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureID);
        currentShader->setUniform1("textureUnitID", textureUnit);

        object->draw(modes[i], starts[i], counts[i]);
    }

}

DrawableObject* Scene::getObject(int index)
{
    if (index >= 0 && index < objects.size())
    {
        return objects[index];
    }

    return nullptr;
}
