#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 frag_col;
out vec2 frag_uv;

void main() {
	frag_col = col;
	frag_uv = uv;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
}