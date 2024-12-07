#version 450
layout(location = 0) in vec3 vp;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform int freeze;
out vec3 fragmentLocalPosition;

void main () {
    
    mat4 viewMatrixEdited;
    if (freeze == 0) {
        viewMatrixEdited = viewMatrix * modelMatrix;
    } else {
        viewMatrixEdited = mat4(mat3(viewMatrix));
    }
    gl_Position = projectionMatrix * viewMatrixEdited * vec4(vp, 1.0);
    fragmentLocalPosition = vp;
    
}