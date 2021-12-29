#version 330 core

// layout
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

// out variables
out vec4 vColor;

// mvp
layout (std140) uniform u_model {
    mat4 modelMatrix;
};

layout (std140) uniform u_view {
    mat4 viewMatrix;
};

layout (std140) uniform u_projection {
    mat4 projectionMatrix;
};

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1.0f);
    vColor = vec4(inColor, 1.0f);
}