#version 330 core

// layout
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

// out variables
out vec4 vColor;

void main() {
    gl_Position = vec4(inPosition, 1.0f);
    vColor = vec4(inColor, 1.0f);
}