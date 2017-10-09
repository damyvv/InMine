#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 frag_col;

void main() {
	frag_col = col;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
}