#version 450
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 vt;
layout(location = 3) in vec3 ts;
uniform mat4 modelMatrix;
out vec2 uv;
void main () {
    uv = vt;
    gl_Position = modelMatrix * vec4(vp, 1.0);
}