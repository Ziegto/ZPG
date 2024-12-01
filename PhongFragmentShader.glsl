#version 450
in vec3 fragmentLocalPosition;
layout(binding = 0) uniform samplerCube UISky;
out vec4 fragColor;
void main() {
    fragColor = texture(UISky, fragmentLocalPosition);
}    

