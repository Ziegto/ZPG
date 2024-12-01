#version 330
layout(location = 0) in vec3 vp;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 fragmentLocalPosition;
void main () {
	mat4 viewMatrixEdited = mat4(mat3(viewMatrix));
	gl_Position = projectionMatrix * viewMatrixEdited * vec4(vp, 1.0);
	fragmentLocalPosition = vp;
}
