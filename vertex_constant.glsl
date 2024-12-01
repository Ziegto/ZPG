#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_UV;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 fragUV;

void main(void) {
    ex_worldPosition = modelMatrix * vec4(in_Position, 1.0);

    ex_worldNormal = mat3(transpose(inverse(modelMatrix))) * in_Normal;

    fragUV = in_UV;

    gl_Position = projectionMatrix * viewMatrix * ex_worldPosition;
}
