#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragNormal;
out vec3 fragPosition;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;
    fragPosition = vec3(modelMatrix * vec4(vp, 1.0));
}