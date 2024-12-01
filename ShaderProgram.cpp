#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "AbstractTransform.h"
#include "AbstractTransform.h"
#include "AbstractTransform.h"
#include "AbstractTransform.h"

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) : shaderLoader(vertexPath, fragmentPath, &programID) {
}

void ShaderProgram::use() {
    glUseProgram(programID);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform3(const char* name, const glm::vec3& vector) {
    glUniform3fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vector));
}

void ShaderProgram::setUniform4(const char* name, const glm::vec4& vector) {
    glUniform4fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vector));
}

void ShaderProgram::update(Subject* subject) {
    
    if (auto camera = dynamic_cast<Camera*>(subject)) {
        use();
        setUniform("viewMatrix", camera->getViewMatrix());
        setUniform("projectionMatrix", camera->getProjectionMatrix());
        setUniform3("cameraPosition", camera->getPosition());
    }

    if (auto light = dynamic_cast<Light*>(subject)) {
        use();
        glUniform3fv(glGetUniformLocation(programID, ("lights[" + std::to_string(light->getId()) + "].position").c_str()), 1, glm::value_ptr(light->getPosition()));
        glUniform4fv(glGetUniformLocation(programID, ("lights[" + std::to_string(light->getId()) + "].color").c_str()), 1, glm::value_ptr(light->getColor()));
        glUniform3fv(glGetUniformLocation(programID, ("lights[" + std::to_string(light->getId()) + "].spotDir").c_str()), 1, glm::value_ptr(light->getLightPosition()));
        glUniform1i(glGetUniformLocation(programID, ("lights[" + std::to_string(light->getId()) + "].type").c_str()), light->getType());
    }
}

void ShaderProgram::setViewMatrix(const glm::mat4& matrix) {
    viewMatrix = matrix; 
}

void ShaderProgram::setProjectionMatrix(const glm::mat4& matrix) {
    projectionMatrix = matrix; 
}

void ShaderProgram::setLights(std::vector<Light*> lights)
{
    this->lights = lights;
}

void ShaderProgram::setNumberLights(int number) const
{
    glUniform1i(glGetUniformLocation(programID, "numLights"), number);
}

void ShaderProgram::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    }
}
