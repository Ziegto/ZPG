#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "Model.h"
#include "ShaderProgram.h"
#include "ComposedTransform.h"

#include "Drawable.h"
#include "Material.h"
#include "SkyCube.h"

class DrawableObject: public Drawable
{
public:
    DrawableObject(AbstractObject* model, ShaderProgram* shader);
    DrawableObject(GLuint vao, ShaderProgram* shader);
    void setTransformation(ComposedTransform* transform) override;
    ComposedTransform* getTransformation();
    glm::mat4 getModelMatrix() const;
    ShaderProgram* getShader() const;
    ~DrawableObject();
    void draw(GLenum mode, int start, int count) override;

    void setSkyCube(SkyCube* skyCube);
    
    void setTexture(GLuint textureID, GLuint textureUnit);
    void setMaterial(Material* material);
    Material* getMaterial() const;

    GLuint getTextureUnit() const { return textureUnit; }
    
protected:
    AbstractObject* model;
    ShaderProgram* shader;
    GLuint vao;
    ComposedTransform* transformation;
    bool usingVAO;
    Material* material;

    GLuint textureUnit;
    GLuint textureID;

    SkyCube* skyCube;
};

#endif // DRAWABLE_OBJECT_H
