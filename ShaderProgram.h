#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "Observer.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "Subject.h"
#include "Light.h"
#include <vector>

class Camera;
class Light;

class ShaderProgram : public Observer
{
public:
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    void use();
    
    void setUniform(const char* name, const glm::mat4& matrix);
    void setUniform1(const char* name, int value);
    void setUniformSkyCube(const char* name, int value);
    void setUniform3(const char* name, const glm::vec3& vector);
    void setUniform4(const char* name, const glm::vec4& vector);

    void update(Subject* subject) override;

    void setViewMatrix(const glm::mat4& matrix);
    void setProjectionMatrix(const glm::mat4& matrix);
    void setNumberLights(int number) const;
    void setLights(std::vector<Light*> lights);

private:
    GLuint programID;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    void checkCompileErrors(GLuint shader, std::string type);
    ShaderLoader shaderLoader;
    std::vector<Light*> lights;
};


#endif
