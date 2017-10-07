#version 330

layout(location = 0) in vec3 pos;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main() {
    gl_Position = projectionMatrix * modelMatrix * vec4(pos, 1);
}