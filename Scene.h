#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "DrawableObject.h"

class DrawableObject;
class Scene
{
public:
    Scene(Camera* cam);
    ~Scene();
    std::vector<ComposedTransform*> getTransforms() const;
    void addObject(DrawableObject* object, GLenum mode, int start, int count);

    void draw();
    DrawableObject* getObject(int index);

    void initLight();
    void addLight(Light* light);

    void setSkyEnabled(bool enabled);

    void setFreezeSkyCube();

    bool lightsInitialized() const;

    void clearLights();
private:
    std::vector<DrawableObject*> objects;
    std::vector<std::pair<DrawableObject*, ComposedTransform*>> modelData;
    std::vector<GLenum> modes;
    std::vector<int> starts;
    std::vector<int> counts;
    std::vector<ShaderProgram*> shaders;
    Camera* camera;
    ShaderProgram* shader;
    std::vector<Light*> lights;

    bool sky = false;
    SkyCube* skyCube;
    DrawableObject* skyCubeDrawable;
    ShaderProgram* shaderSkyCube;
    int freezeSkyCube = 0;
    bool lightsInitializedFlag = false;

};
