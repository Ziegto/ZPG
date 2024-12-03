#include "Scene.h"
#include <glm/gtc/type_ptr.hpp>

#include "SkyCube.h"
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
    for(int i = 0; i < lights.size(); i++)
    {
        lights[i]->setId(i);
        lights[i]->notify();
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

void Scene::draw() {
    if (sky) {
        skyCubeDrawable->draw(GL_TRIANGLES, 0, 36);
    }
    
    for (size_t i = 0; i < objects.size(); ++i) {
        DrawableObject* object = objects[i];
        ShaderProgram* currentShader = object->getShader();
        Material* material = object->getMaterial();

        currentShader->setNumberLights(lights.size());
        currentShader->use();

        glm::mat4 modelMatrix = object->getModelMatrix();
        currentShader->setUniform("modelMatrix", modelMatrix);

        if (material) {
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
