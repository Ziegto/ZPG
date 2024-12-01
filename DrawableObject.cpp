#include "DrawableObject.h"
#include "Model.h"

DrawableObject::DrawableObject(AbstractObject* model, ShaderProgram* shader)
    : model(model), shader(shader), vao(0), usingVAO(false), material(nullptr)
{
}

DrawableObject::DrawableObject(GLuint vao, ShaderProgram* shader)
    : model(nullptr), shader(shader), vao(vao), usingVAO(true), material(nullptr)
{
}

void DrawableObject::setTexture(GLuint textureID, GLuint textureUnit) {
    this->textureID = textureID;
    this->textureUnit = textureUnit;
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
    glActiveTexture(GL_TEXTURE + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    shader->setUniform("textureUnitID", textureUnit);
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