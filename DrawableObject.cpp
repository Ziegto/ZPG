#include "DrawableObject.h"

#include <SOIL.h>

#include "Model.h"

DrawableObject::DrawableObject(AbstractObject* model, ShaderProgram* shader)
    : model(model), shader(shader), vao(0), usingVAO(false), material(nullptr)
{
}

DrawableObject::DrawableObject(GLuint vao, ShaderProgram* shader)
    : model(nullptr), shader(shader), vao(vao), usingVAO(true), material(nullptr)
{
}

void DrawableObject::setTexture(GLuint textureUnit, string path) {
    this->textureUnit = textureUnit;

    this->textureID = SOIL_load_OGL_texture(
        path.c_str(),
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (this->textureID == 0) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


void DrawableObject::setMaterial(Material* mat) {
    material = mat;
}

Material* DrawableObject::getMaterial() const {
    return material;
}

void DrawableObject::setTransformation(ComposedTransform* transform)
{
    transformation = transform;
}

ComposedTransform* DrawableObject::getTransformation()
{
    return transformation;
}

void DrawableObject::draw(GLenum mode, int start, int count) {
    shader->use();
    model->draw();
}


glm::mat4 DrawableObject::getModelMatrix() const
{
    return transformation ? transformation->getTransformMatrix() : glm::mat4(1.0f);
}

ShaderProgram* DrawableObject::getShader() const
{
    return shader;
}

DrawableObject::~DrawableObject()
{
}